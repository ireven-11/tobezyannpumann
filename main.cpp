#include"includeAll.h"

int WINAPI WinMain(winmainSetting)
{
    //終了変数
    int end = standardNumber;

    end = setScreen();
    if (end == -1)
    {
        return -1;
    }
    end = setEffekseer();
    if (end == -1)
    {
        return -1;
    }
    
    bool  isPrevButton          = false;                                        //前フレームにキー押したかフラグ
    int   staminaRedGage        = LoadGraph("img/redcircle.png");             //スタミナゲージ(赤)
    bool  canPlayGame           = false;                                        //ゲームできるかフラグ
    bool  cannotSpawnTwoItems   = false;                                        //二つ目のアイテム出現できるかフラグ
   
    //インスタンス化
    Bird* bird[maxBirdNumber];
    for (int i = 0; i < maxBirdNumber; i++)
    {
        bird[i] = new Bird(i);
    }
    Player* player              = new Player();
    BackGraph* backGraph        = new BackGraph();
    Camera* camera              = new Camera();
    TitleGraph* titleGraph      = new TitleGraph();
    SelectScene* selectScene    = new SelectScene();
    ProceedScene* proceedScene  = new ProceedScene();
    UI* ui                      = new UI();
    ClearGraph* clearGraph      = new ClearGraph();
    Animation* animation        = new Animation(player, bird);
    Effect* effect              = new Effect();
    Transition* transition      = new Transition();
    //Item* item                  = new Item();
    Rocket* rocket              = new Rocket();
    Wing* wing                  = new Wing();
    Shield* shield              = new Shield();
    CupCake* cupCake            = new CupCake();
    Routine* routine            = new Routine();
    Timer* timer                = new Timer();
    SandClock* sandClock        = new SandClock();
    UFO* ufo                    = new UFO();
    ChargeEffect* chargeEffect  = new ChargeEffect();

    //音
    bool canPlayBGM         = true;
    bool canPlayClearSound  = true;                                  

    transition->Init();
    
    //ゲームループ
    routine->gameRoop_(camera, player, titleGraph, ui, selectScene, canPlayBGM, proceedScene, backGraph, bird, timer, isPrevButton, staminaRedGage, canPlayClearSound, animation,
        canPlayGame, effect, rocket, shield, wing, cupCake, cannotSpawnTwoItems, transition, clearGraph, sandClock,ufo,chargeEffect);

    //Effekseerを終了する。
    Effkseer_End();

    //デリートの代わり
    animation->Delete_(player, bird);
    
    delete(player);
    delete(backGraph);
    //delete(bird);
    delete(camera);
    delete(titleGraph);
    delete(selectScene);
    delete(proceedScene);
    delete(ui);
    delete(clearGraph);
    delete(effect);
    delete(transition);
    //delete(item);
    delete(rocket);
    delete(wing);
    delete(shield);
    delete(cupCake);
    delete(routine);
    delete(timer);
    delete(sandClock);
    delete(ufo);

    DxLib_End();
    return 0;
}