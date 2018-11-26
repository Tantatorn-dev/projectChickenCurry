#include "mainCharacter.h"

mainCharacter::mainCharacter(Setup *passed_setup, float *passed_cameraX, float *passed_cameraY, worldMap *passed_Map)
{
    Map = passed_Map;

    cameraX = passed_cameraX;
    cameraY = passed_cameraY;

    sdlSetup = passed_setup;

    Lo = new sprite(sdlSetup->getRenderer(), "resource/image/Lo.png", 1200, 900, 50, 75, cameraX, cameraY, collisionRectangle(0, 50, 50, 25));
    Lo->setUpAnimation(4, 4);
    direction = STILL;

    level = 1;
    experience = 0;
    maxHP = 60;
    maxMP = 20;
    hp = maxHP;
    mp = maxMP;
    attack = 10;
    defense = 5;
    gold = 100;
    intelligence = 8;

    loTextRect.x = 10;
    loTextRect.y = 550;
    loTextRect.w = 40;
    loTextRect.h = 60;

    hpTextRect.x = 60;
    hpTextRect.y = 550;
    hpTextRect.w = 80;
    hpTextRect.h = 30;

    mpTextRect.x = 60;
    mpTextRect.y = 572;
    mpTextRect.w = 80;
    mpTextRect.h = 30;

    goldTextRect.x = 680;
    goldTextRect.y = 550;
    goldTextRect.w = 80;
    goldTextRect.h = 30;

    levelTextRect.x = 680;
    levelTextRect.y = 572;
    levelTextRect.w = 80;
    levelTextRect.h = 30;

    perk = 0;

    spacebar = NULL;
    spacebar = IMG_LoadTexture(sdlSetup->getRenderer(), "resource/image/spacebar.png");
    spacebarRect = {320, 250, 200, 50};
    interactRect = {365, 200, 100, 50};

    eType = MINIONS;
}

mainCharacter::~mainCharacter()
{
    delete sdlSetup;

    delete Lo;
    delete Map;

    delete cameraX;
    delete cameraY;

    SDL_DestroyTexture(spacebar);
    spacebar = NULL;
}

void mainCharacter::resetCharacter()
{
    level = 1;
    experience = 0;
    maxHP = 60;
    maxMP = 20;
    hp = maxHP;
    mp = maxMP;
    attack = 10;
    defense = 5;
    gold = 100;
    intelligence = 8;

    perk = 0;

    Lo->setX(1200);
    Lo->setY(900);

    for (int i = 0; i < 4; i++)
    {
        sdlSetup->bossKilled[i] = false;
    }

    *cameraX = -800;
    *cameraY = -600;
}

void mainCharacter::draw()
{
    Lo->draw();
}

void mainCharacter::update()
{
    directionPlayAnimation(direction);

    if (sdlSetup->getMainEvent()->type == SDL_KEYUP)
    {
        direction = STILL;
    }

    checkInCircle();

    if (sdlSetup->getMainEvent()->type == SDL_KEYDOWN)
    {
        colliding = false;
        for (int i = 0; i < 10; i++)
        {
            if (Lo->isCollide(Map->getTrees()[i]->getTrunk()->getCollisionRect()))
            {
                colliding = true;
            }
        }

        for (int i = 0; i < 4; i++)
        {
            if (Lo->isCollide(Map->getCliff()[i]->getCollisionRect()))
            {
                colliding = true;
            }
        }

        if (Lo->isCollide(Map->getWaterfall()->getCollisionRect()))
        {
            colliding = true;
        }

        for (int i = 0; i < 4; i++)
        {
            if (Lo->isCollide(Map->getRiver1()[i]->getCollisionRect()))
            {
                colliding = true;
            }
        }

        if (step <= 200)
        {
            if (!colliding)
            {
                switch (sdlSetup->getMainEvent()->key.keysym.sym)
                {
                case SDLK_w:
                    Lo->setY(Lo->getY() - 5);
                    direction = UP;
                    prevDirection = UP;
                    *cameraY += 5;
                    step++;
                    break;
                case SDLK_a:
                    Lo->setX(Lo->getX() - 5);
                    direction = LEFT;
                    prevDirection = LEFT;
                    *cameraX += 5;
                    step++;
                    break;
                case SDLK_s:
                    Lo->setY(Lo->getY() + 5);
                    direction = DOWN;
                    prevDirection = DOWN;
                    *cameraY -= 5;
                    step++;
                    break;
                case SDLK_d:
                    Lo->setX(Lo->getX() + 5);
                    direction = RIGHT;
                    prevDirection = RIGHT;
                    *cameraX -= 5;
                    step++;
                    break;
                default:
                    break;
                }
            }
            else
            {
                switch (prevDirection)
                {
                case RIGHT:
                    Lo->setX(Lo->getX() - 1);
                    *cameraX += 1;
                    break;
                case LEFT:
                    Lo->setX(Lo->getX() + 1);
                    *cameraX -= 1;
                    break;
                case UP:
                    Lo->setY(Lo->getY() + 1);
                    *cameraY -= 1;
                    break;
                case DOWN:
                    Lo->setY(Lo->getY() - 1);
                    *cameraY += 1;
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void mainCharacter::directionPlayAnimation(int passed_direction)
{
    if (passed_direction == DOWN)
    {
        Lo->playAnimation(0, 3, 0, 500.00);
    }
    else if (passed_direction == RIGHT)
    {
        Lo->playAnimation(0, 3, 1, 500.00);
    }
    else if (passed_direction == UP)
    {
        Lo->playAnimation(0, 3, 2, 500.00);
    }
    else if (passed_direction == LEFT)
    {
        Lo->playAnimation(0, 3, 3, 500.00);
    }
    else if (passed_direction == STILL)
    {
        switch (prevDirection)
        {
        case LEFT:
            Lo->playAnimation(0, 0, 3, 500.00);
            break;
        case DOWN:
            Lo->playAnimation(0, 0, 0, 500.00);
            break;
        case RIGHT:
            Lo->playAnimation(0, 0, 1, 500.00);
            break;
        case UP:
            Lo->playAnimation(0, 0, 2, 500.00);
            break;
        default:
            Lo->playAnimation(0, 0, 0, 500.00);
            break;
        }
    }
}

int mainCharacter::getATK()
{
    return attack;
}

void mainCharacter::setATK(int passed_atk)
{
    attack = passed_atk;
}

int mainCharacter::getDEF()
{
    return defense;
}

void mainCharacter::setDEF(int passed_def)
{
    defense = passed_def;
}

void mainCharacter::drawHUD()
{
    sdlSetup->loadFromRenderedText("Lo", white, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &loTextRect);
    sdlSetup->clearText();

    std::string hpString = std::to_string(hp);
    std::string maxHpString = std::to_string(maxHP);
    sdlSetup->loadFromRenderedText("HP " + hpString + '/' + maxHpString, white, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &hpTextRect);
    sdlSetup->clearText();

    std::string mpString = std::to_string(mp);
    std::string maxMpString = std::to_string(maxMP);
    sdlSetup->loadFromRenderedText("MP " + mpString + '/' + maxMpString, white, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &mpTextRect);
    sdlSetup->clearText();

    std::string goldString = std::to_string(gold);
    sdlSetup->loadFromRenderedText("GOLD " + goldString, white, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &goldTextRect);
    sdlSetup->clearText();

    std::string levelString = std::to_string(level);
    sdlSetup->loadFromRenderedText("LEVEL " + levelString, white, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &levelTextRect);
    sdlSetup->clearText();
}

int mainCharacter::getHP()
{
    return hp;
}

void mainCharacter::setHP(int passed_hp)
{
    hp = passed_hp;
}

int mainCharacter::getMP()
{
    return mp;
}

int mainCharacter::getGold()
{
    return gold;
}

void mainCharacter::setGold(int passed_gold)
{
    gold = passed_gold;
}

int mainCharacter::getExp()
{
    return experience;
}

void mainCharacter::setExp(int passed_exp)
{
    experience = passed_exp;
}

void mainCharacter::setMP(int passed_mp)
{
    mp = passed_mp;
}

int mainCharacter::getStep()
{
    return step;
}

void mainCharacter::setStep()
{
    step = 0;
}

int mainCharacter::getINT()
{
    return intelligence;
}

void mainCharacter::setINT(int passed_int)
{
    intelligence = passed_int;
}

int mainCharacter::getMaxHP()
{
    return maxHP;
}

void mainCharacter::setMaxHP(int passed_maxHP)
{
    maxHP = passed_maxHP;
}

int mainCharacter::getMaxMP()
{
    return maxMP;
}

void mainCharacter::setMaxMP(int passed_maxMP)
{
    maxMP = passed_maxMP;
}

int mainCharacter::getLVL()
{
    return level;
}

int mainCharacter::getPotionAmout()
{
    return potion.itemAmout;
}

void mainCharacter::setPotionAmout(int passed_amout)
{
    potion.itemAmout = passed_amout;
}

int mainCharacter::getElixirAmout()
{
    return elixir.itemAmout;
}

void mainCharacter::setElixirAmout(int passed_amout)
{
    elixir.itemAmout = passed_amout;
}

int mainCharacter::getPerk()
{
    return perk;
}

void mainCharacter::setPerk(int passed_perk)
{
    perk = passed_perk;
}

void mainCharacter::levelUp()
{
    if (experience - (50 * level) >= 0)
    {
        experience = experience - (50 * level);
        level++;
        perk += 10;
    }
}

void mainCharacter::saveGame()
{

    saveFile["playerName"] = sdlSetup->getPlayerName();

    saveFile["hp"] = 23;
    saveFile["maxHP"] = maxHP;
    saveFile["mp"] = mp;
    saveFile["maxMP"] = maxMP;
    saveFile["gold"] = gold;
    saveFile["level"] = level;
    saveFile["experience"] = experience;
    saveFile["perk"] = perk;
    saveFile["attack"] = attack;
    saveFile["defense"] = defense;
    saveFile["intelligence"] = intelligence;

    saveFile["PosX"] = Lo->getX();
    saveFile["PosY"] = Lo->getY();

    saveFile["potion"] = potion.itemAmout;
    saveFile["elixir"] = potion.itemAmout;

    saveFile["bossKilled1"] = sdlSetup->bossKilled[0];
    saveFile["bossKilled2"] = sdlSetup->bossKilled[1];
    saveFile["bossKilled3"] = sdlSetup->bossKilled[2];
    saveFile["bossKilled4"] = sdlSetup->bossKilled[3];

    switch (sdlSetup->saveState)
    {
    case SAVE_1:
    {
        std::ofstream o1("saveFile1.json");
        o1 << std::setw(4) << saveFile.dump() << std::endl;
        break;
    }
    case SAVE_2:
    {
        std::ofstream o2("saveFile2.json");
        o2 << std::setw(4) << saveFile.dump() << std::endl;
        break;
    }
    case SAVE_3:
    {
        std::ofstream o3("saveFile3.json");
        o3 << std::setw(4) << saveFile.dump() << std::endl;
        break;
    }
    case SAVE_4:
    {
        std::ofstream o4("saveFile4.json");
        o4 << std::setw(4) << saveFile.dump() << std::endl;
        break;
    }
    case SAVE_5:
    {
        std::ofstream o5("saveFile5.json");
        o5 << std::setw(4) << saveFile.dump() << std::endl;
        break;
    }
    default:
        break;
    }
}

void mainCharacter::loadGame()
{
    std::ifstream i1("saveFile1.json");
    std::ifstream i2("saveFile2.json");
    std::ifstream i3("saveFile3.json");
    std::ifstream i4("saveFile4.json");
    std::ifstream i5("saveFile5.json");
    switch (sdlSetup->saveState)
    {
    case SAVE_1:
        saveFile << i1;
        break;
    case SAVE_2:
        saveFile << i2;
        break;
    case SAVE_3:
        saveFile << i3;
        break;
    case SAVE_4:
        saveFile << i4;
        break;
    case SAVE_5:
        saveFile << i5;
        break;
    default:
        break;
    }

    Lo->setX(saveFile["PosX"]);
    Lo->setY(saveFile["PosY"]);

    setCamera(Lo->getX(), Lo->getY());

    sdlSetup->setPlayerName(saveFile["playerName"]);

    gold = saveFile["gold"];
    hp = saveFile["hp"];
    maxHP = saveFile["maxHP"];
    mp = saveFile["mp"];
    maxMP = saveFile["maxMP"];
    experience = saveFile["experience"];
    level = saveFile["level"];
    attack = saveFile["attack"];
    defense = saveFile["defense"];
    intelligence = saveFile["intelligence"];
    perk = saveFile["perk"];

    sdlSetup->bossKilled[0] = saveFile["bossKilled1"];
    sdlSetup->bossKilled[1] = saveFile["bossKilled2"];
    sdlSetup->bossKilled[2] = saveFile["bossKilled3"];
    sdlSetup->bossKilled[3] = saveFile["bossKilled4"];

    potion.itemAmout = saveFile["potion"];
    elixir.itemAmout = saveFile["elixir"];
}

void mainCharacter::setCamera(int x, int y)
{
    *cameraX = *cameraX + 1200 - x;
    *cameraY = *cameraY + 900 - y;
}

void mainCharacter::checkInCircle()
{
    if (!sdlSetup->bossKilled[0])
    {
        if (Lo->isCollide(Map->getSummonCircleGreen()->getCollisionRect()))
        {
            Map->getSummonCircleGreen()->summoning = true;
            drawInteractPrompt();
            if (sdlSetup->getMainEvent()->key.keysym.sym == SDLK_SPACE)
            {
                this->step = 201;
                this->eType = BOSS_1;
                Map->getSummonCircleGreen()->destroy();
                sdlSetup->bossKilled[0] = true;
            }
        }
        else
        {
            Map->getSummonCircleGreen()->summoning = false;
        }
    }

    if (!sdlSetup->bossKilled[1])
    {
        if (Lo->isCollide(Map->getSummonCircleBlue()->getCollisionRect()))
        {
            Map->getSummonCircleBlue()->summoning = true;
            drawInteractPrompt();
            if (sdlSetup->getMainEvent()->key.keysym.sym == SDLK_SPACE)
            {
                this->step = 201;
                this->eType = BOSS_2;
                Map->getSummonCircleBlue()->destroy();
                sdlSetup->bossKilled[1] = true;
            }
        }
        else
        {
            Map->getSummonCircleBlue()->summoning = false;
        }
    }

    if (!sdlSetup->bossKilled[2])
    {
        if (Lo->isCollide(Map->getSummonCirclePurple()->getCollisionRect()))
        {
            Map->getSummonCirclePurple()->summoning = true;
            drawInteractPrompt();
            if (sdlSetup->getMainEvent()->key.keysym.sym == SDLK_SPACE)
            {
                this->step = 201;
                this->eType = BOSS_3;
                Map->getSummonCirclePurple()->destroy();
                sdlSetup->bossKilled[2] = true;
            }
        }
        else
        {
            Map->getSummonCirclePurple()->summoning = false;
        }
    }

    if (!sdlSetup->bossKilled[3])
    {
        if (Lo->isCollide(Map->getSummonCircleRed()->getCollisionRect()))
        {
            Map->getSummonCircleRed()->summoning = true;
            drawInteractPrompt();
            if (sdlSetup->getMainEvent()->key.keysym.sym == SDLK_SPACE)
            {
                this->step = 201;
                this->eType = BOSS_4;
                Map->getSummonCircleRed()->destroy();
                sdlSetup->bossKilled[3] = true;
            }
        }
        else
        {
            Map->getSummonCircleRed()->summoning = false;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (sdlSetup->bossKilled[i])
        {
            switch (i)
            {
            case 0:
                Map->getSummonCircleGreen()->destroy();
                break;
            case 1:
                Map->getSummonCircleBlue()->destroy();
                break;
            case 2:
                Map->getSummonCirclePurple()->destroy();
                break;
            case 3:
                Map->getSummonCircleRed()->destroy();
                break;
            default:
                break;
            }
        }
    }
}

void mainCharacter::drawInteractPrompt()
{
    SDL_RenderCopy(sdlSetup->getRenderer(), spacebar, NULL, &spacebarRect);

    sdlSetup->loadFromRenderedText("interact", {255, 255, 255}, BAHNSCHRIFT);
    SDL_RenderCopy(sdlSetup->getRenderer(), sdlSetup->getTextTexture(), NULL, &interactRect);
    sdlSetup->clearText();
}