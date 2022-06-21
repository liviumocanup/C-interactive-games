#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

//-------------------------------------------------------------------Two-tap generalised feedback shift register(Lagged Fibbonacci XOR)-------------------------------------------------------------------//

unsigned long long fRandF[521];
int posRandF, aRandF=521, bRandF = 353;

void initRandF(unsigned long long seed)
{
    unsigned long long int dRandF[521] =
        {0x1D9AC40058963296, 0xCD8EA4C06B50F012, 0x8471FC7B0304296, 0x908CC4BA165CDFCB, 0x9DB8EE748BE324DC, 0xB63AA64B14BD1DAD,
        0x39EA2F142AF97B5D, 0x867064F81B199C99, 0xD3E2F1BAD5E45E4, 0x5CD5689FCD69C90E, 0x34910BCD8B443F9C, 0xD7A288601537CEC6,
        0xB979A55B721DA9F7, 0x984354E76410DAE2, 0x744F406438808443, 0xFEE2CBDE6F6263BB, 0x4E4D145C55F2C6A0, 0x1B07786BBDC5B7A,
        0x3A929540ED3A9F53, 0x9E75D1AE243F5E0C, 0x5F54E30727DB95AC, 0x10023120082F4628, 0xF6D1101BD2FE4E34, 0x1F0CCE30C35B315A,
        0xCF70F152A03F1676, 0x860F5901AA72F87C, 0xA448ECF927CE1801, 0xE49470D2C75E80DC, 0xCC92167F2DA00B88, 0x30B0C004B42D3EE9,
        0x5002769C8C076083, 0x60A28163C9303D99, 0xBE59E7C030194EE2, 0x676BE7EB077DD683, 0x31CA9391D3D007B2, 0xFA115B2499404176,
        0x21D67C10CCE76B7B, 0x147E6E3B576A83AF, 0x871D6C29D60F2CD4, 0xCAB10D1E9FD81B7D, 0xB97217DDA546212D, 0x7F316A8E99231F34,
        0x64EF13CBC39C9D9F, 0x58AB8701EAA3D89B, 0x4ECFBB5955D8BFFB, 0x634A9672666B2FB4, 0xE6E6F5E20661C314, 0xDC4F02A4F363567B,
        0xD3D37D99F58EC943, 0x6FAB733BFECB46D2, 0x737CAA2A0A4D061E, 0x1E3C1571C7569618, 0x8F05B5A0B682D9C5, 0x3FA3AF3A426C68E9,
        0xED702129B85199E6, 0x5238AE3B73F991B8, 0x587D69BADCF95A16, 0xBDFEFE689E546B23, 0x67D7182F79F0D1BA, 0x26F8CD2C884D585C,
        0xE14BA811E7C4173A, 0xDF712E080847AAF2, 0xEEC8011F7151F2E1, 0xEE84CED58A6F7AA0, 0x3FE6FA362101CE48, 0x4F3A36C27F29E942,
        0x49BD68174DAB0975, 0x178A1A69DAE50F45, 0xAC6C436206EA08A2, 0x5AAAFF0E1057F6E0, 0x70120C43C7990404, 0xC0D35C7E0DFB509B,
        0xCD68BDDF6462DA3C, 0x5895D715053C7ADB, 0xA4166CE939C253CF, 0x62E5DABF132A72A9, 0xE357BC79C7777DB3, 0x66944E3B9118DBC4,
        0xA469987D718A6B31, 0xC7FA851425A06B81, 0x4CB82897BBF4A328, 0x528004EF242FD9ED, 0xEFCB8F2D287F8F18, 0xB774C65F7D1FA0BB,
        0x3537CF073967F1C5, 0xC8D8F1D44B77354E, 0x5CDD866671A65277, 0x893B95C810615A80, 0xA9293F841C490046, 0x9EED3BCEEFD7E021,
        0xEB2FEC8DCC9F314F, 0x6771BC80EC87A0A0, 0x7E0394E79A898951, 0xC0F32BFFA5DC45C5, 0x580A4CDA4C19F5EE, 0xFF16F1D0852E8626,
        0x66D3C8D715E760E3, 0x2F2B95743ED08AEE, 0xA5BF910681DFD673, 0xD057D17D49A6597B, 0x7AD14344DBFBCEFB, 0x75FAB7FACC989B4D,
        0x32FC0ED5B7BD3626, 0x58EB4DF1A59D9666, 0xB0A955DD8D5BA90, 0xF9840B8C6A3538E8, 0xABA4D27D0EE85EF6, 0x7BD5D4E00EB3D0B1,
        0x593A60ED8FE45E0C, 0xF46E9700D3E82D2E, 0x9C4A93D4A5114384, 0x26592F64235581B2, 0x8AE9482564735DE3, 0x6F7336A31C8EE91C,
        0x4BFD35CE2FC5E302, 0x2A2FCBF8A0536B98, 0xE55AA1C7E6A96B6C, 0x10CA02A322BB4D17, 0xFEAF0568D5A795E2, 0x7B26846024685F85,
        0xB1909EA1F93B6CF6, 0x4ED5BECBED3977F4, 0x5D94D6AA7E75A876, 0xC0AFE7D39E1AA413, 0x82491861E084C9B5, 0x199A51297161C414,
        0x8FAC443F34F9838C, 0x19873A7460E7807F, 0xA40685B476AE47A7, 0x7DE62C4F5A8AF886, 0xF8A1F8A877D49ADD, 0xEAC3B443979072EC,
        0xDFDE360EEAF1FD6F, 0xC417972D443164BE, 0xCDD7F819B9C26A54, 0x184C19FB95B437E3, 0xBEDDA5C50214A909, 0xCC6C743DC9C134CB,
        0x9477B0FABCFB5D73, 0x2B2169C964CE611A, 0xC5C398040CDD1DD4, 0x74BD65D929710BC2, 0x78C5BFD534FF5A3A, 0xF965EDF820692D38,
        0x385697FB4D35DDDE, 0x416D9A67B407CEF5, 0xFFA889442C062984, 0x19397CD52F3982EA, 0xB4DB06669EF7635, 0x729AF2B8CD7C032F,
        0xF7D3716CBF8CCA7F, 0xB335DA0FCF77D4C3, 0x4C70E0EC54F03FEC, 0xB91AD92F6E95980D, 0x912B8E5460DA0A97, 0x96BD3EED8E83DE56,
        0xDBF9F5AAD9D85854, 0x6950B17C192CD268, 0x20F450FC1952CFAB, 0x51DE83E43D9ED890, 0x8B49B43EA8DB8FD7, 0x7E0CA89C22D274FB,
        0xAD47EAEA277985FF, 0x35DCB03108E3390E, 0xE17FA6BF323832D9, 0x63E2A75C7C8B2952, 0x17512C927668E78E, 0x9AE419AF6501345E,
        0x3CC8BBF4B20661B2, 0x87958764A0120EE4, 0x9D32EE51544760D9, 0xF26E85C01E45AB95, 0xB8946342CE9D65FB, 0x926C55C4581C3D03,
        0x5DA25D7C838F7AAB, 0xEAA1EF7A49B7DD49, 0xA546F6AC61210F8A, 0xB06212187597E960, 0xBB6F1BDFA60948A9, 0x2F25BAC1936A426A,
        0x281B1EF8CF043433, 0x66CF61B82D5E0B22, 0x90173A926C1B8CCD, 0xC548F5741AE64F49, 0x526B0275113B7733, 0xBF12C4FC04F49572,
        0xAA6866174DB81EF2, 0xCA4150FE32E961D0, 0x67BDFB98A2901E73, 0xBBDD68979E0280, 0x4D5A3EA631880F94, 0xB4EFBCFA33D9BD68,
        0xEF486EB355F7247D, 0xCB1FDA012346F72D, 0x969C42C597316638, 0x78B8E72C757B82E3, 0x78D3ED4B0E53759D, 0x8235AF78B86917CB,
        0x8E026C713A674D6, 0xFC32C6F62DF33F22, 0x330FB8ABC9C3FED5, 0xCD25EDCF2AC16DB9, 0x1AC5003C3650673C, 0x10675DDA20403B26,
        0x82A3C8A373746A60, 0xB460C0ADF69BE2CA, 0xF14188DCE2C981B8, 0x28DD139FD47BF70E, 0x55F4441877A99675, 0x8150663FD581FDBA,
        0xCFE901E64DF9B342, 0x27CF43B909676F64, 0x2B4260BEFF3CA474, 0xC8E0A43802684104, 0x1EA3950A1DF82CCF, 0x14F75D79875364BE,
        0xEC80A9CF822635BC, 0xFCDAC1BFD25F1FDF, 0xCFFF8388901564B, 0x5586AA72FD11238, 0xB3313191EB3A8624, 0xAD3DE6EC4F29193E,
        0xE607AEEC8E94EA7B, 0xFA7DC8ADA73BFFC2, 0x4F7E0BA491BC6E7F, 0x9D18226D8E44A154, 0xD9508AC3744EE3F6, 0x37871C01F8EF8BCC,
        0x422340BB66DDCACF, 0xE51CD6BA1EBB85A, 0xD625A9AD4F8C75C, 0x85FAD1D437E13952, 0x8028ECFCF0E53F7, 0xD3D2CE944B4855C3,
        0x8244F0152CCFC078, 0xD2AD4C15E8EE2CD5, 0x2C5102A7458C40C0, 0xEE7C44F08E911827, 0x79A20D461DA87D6E, 0xD9562C9FA6623ED9,
        0x65DFA46E7256969E, 0xBD882EA9A74292D4, 0xD5ADB03135920EB4, 0x15B2713AB8785DB6, 0x89E6D7CC94A98FEF, 0x539FEB8D93311402,
        0xED07E153C22BED1E, 0x7EAC7AB232241480, 0x3C39C501ED1821F8, 0x8217D79CFBF4A968, 0xB6A5A2C7259D7AC8, 0x498AED9AA02255F3,
        0x93AF3268E200B581, 0x9AA950C664E69755, 0x28C4A0D9553D10DD, 0x178A5785DE93E218, 0x625D23F20FD7A33A, 0x39EDDEA0BC10C42A,
        0x592CED161E31BCF8, 0xE0BCF5E578BA077D, 0x3827D23DA5342AD3, 0x5ABB45CE48C73EB1, 0x48D0AD1C952D362C, 0x943E2881ED4BD864,
        0xB47B71CC6F2B693E, 0x17C6CDEFBDF7C548, 0xFDAF0CAB76BAD11A, 0x603CB6FE93216E08, 0x64AF7E09379D7A44, 0x86472A7B0237C68D,
        0xA7D23598B3E29A53, 0x96EF3A419251BF01, 0x6E9CA8019B62C2F, 0x181DA916227E31C2, 0x71893437F50519F0, 0xB6FAE83524FF73D5,
        0x63621D96B5E7D7CB, 0x4E7ED2FF95527ECA, 0x38AF78C90A0A1FA5, 0x84F77BC2FB3BD945, 0x48CBD9F323E5B5FB, 0x1B289FD0D8B9091D,
        0x850E73DB53DCC50C, 0xBB8F83A59C8CE7FD, 0x326DC1EF8EB070E6, 0x867801B844E35D62, 0x4824E7F55AABD2AD, 0x870426623FE6BF91,
        0xBB76079AA648D0EC, 0xE4B77FBB63B62793, 0x2BE7A71A689D7CCD, 0xC7DA7D78C060955E, 0x992EE7A9BE4BC8DE, 0x472ACE229B82FF9A,
        0xC3BEBEEABF9267CA, 0x510CE96C54795FA1, 0x1D0B63741DA7423B, 0xB8DA95226A7E7E62, 0x843A4FBA405EF6EC, 0xB44F8FAF995054D2,
        0x8721B54A413A7691, 0x7B36C233C98A7A5A, 0xD00C0C758967EC0B, 0xCAB96555B21DA4D9, 0x654E628008D2B137, 0x9F4717A81E39CF00,
        0xE45CDAA6909DF7FD, 0x33FAC9F58B36A6FA, 0xF2EE131627F79D5A, 0x91704138B845FDEB, 0x7F6589639661DE28, 0x5DAC3E20418AE5B5,
        0x7DC6F86FC0D3B26F, 0x32BFFB07386A0F9, 0x3C27F0CE892E9B08, 0x4540415C5739497, 0x755079169E25D222, 0x258533D6D7A8125D,
        0x7F5855A12B44DE99, 0xFB4043E2470AC237, 0x70B35A44B64DCA83, 0x4E24582B16B3A4B0, 0x31C675FB596CD7D3, 0xCA9C968062DEFFEA,
        0x3341C748351C9989, 0x1B1D5227FFEFD657, 0xEC95259C00FF65D5, 0xE7BA6EC4879CB4D8, 0xE1B2CAABDCA5819A, 0x7904BD26B7420B79,
        0xE5FD68FF3BC59482, 0xF28FCB28C507230C, 0x4FE634A69F90680C, 0xF74311D3C2794B9, 0x487FD600E2C537AE, 0xB61501BD5726C13D,
        0x57F702E9764746E, 0x88EB6474450089C0, 0x85F0FD9A4B80413C, 0xC34A837811013861, 0xE90BFF687D2C640F, 0x3C2DADFF78A91E7C,
        0x424BCCD08618D7A2, 0x204526ED4E00D8AC, 0x9A22109095449597, 0x96858A97783294AA, 0xC1E4EFB1554D61B6, 0x302EAFF7BA4C5455,
        0xBB0BC02B166BE0C7, 0xFFA3B2644F39954B, 0x309D1C209369A9BE, 0x9C57D0EF9F0CD722, 0xEE86B79338A846A6, 0xA95D6E9A8534E281,
        0x7C22775C75B4BD2D, 0x5F1CC68C14BE4DE3, 0x2444E2D08380167, 0x627E2A2A52D2CB62, 0x22528D67803C225C, 0xA71608BBB51EC5A,
        0x8E3C4EEC0FFEFC81, 0xA349A4350F56D5CE, 0xB6EB92D0DC378D82, 0x9466A973A3A61179, 0x7C86A2A607EB2F7D, 0xFF16ECA021F160FA,
        0x8042CE3C41C0AACF, 0x9BAAF8B85582E9E7, 0xD64C88DBA86CCEB0, 0x324D565E57248D55, 0x20D54E0C31063F14, 0x8592D0D9755414AB,
        0x424C0088030E3818, 0x571F08DE3DD2E243, 0x772B2AEE856AC3FE, 0xED610A168D671D5C, 0x746533D96D1311C8, 0x57F7DD856B293275,
        0x43A98F6277FCE4CC, 0x1A66C7A6EE9B2950, 0xDEEB12B289C6FAC, 0x225F2B804B7196D0, 0xC5B11A9FDEDBE56C, 0xA5DB27C74E14A96B,
        0x493E64726C6EFFF4, 0xB3DEC2186E70761D, 0x2E70E9DB43D90DB5, 0x1E3A1611A6111180, 0x7F5A72C488FDD9ED, 0xA87858774285F443,
        0x9B1649D43630C9F6, 0x4DC7B957B3070582, 0x3A9FD96517F9F9A1, 0xEF2A00B0BFA724EE, 0xBB1E4A86407F68BA, 0x781D0FCB77405D2F,
        0xC56A815F39E90EB5, 0xF4D15857E1AF1FC4, 0x38B2B6EF1A9233A8, 0x840A2D2D97C21511, 0x8A17FB345ED2EB58, 0x46B3F8C0DF2E2D4F,
        0x624C8B159465B358, 0x59185C18C4956FB4, 0xAECCC277A37EEA82, 0xBD41C3D9B923EFFF, 0x3C1FD2686575A67E, 0xF4250CCCF83793EA,
        0x7C42E0E7C0E573F1, 0x57162EAD4C1D39D4, 0xA32BF8869E9DA688, 0xCF52CD6BCA95867B, 0x9C7059B71090AF6A, 0xF2AE0374D91FDDD5,
        0x52D9092B53C10774, 0xE47712FC393F2216, 0x8DB9AF045F037C54, 0xAC1A022B912A6E99, 0x57E52A28F654E233, 0x7C07D27F6ED55C4C,
        0xA6A119C0B546C63B, 0xB862E7B56C435C7, 0x16E87B2448F7B6A8, 0xB2392CEC9757B7BB, 0xC531D95F19ADFFFF, 0xA2398CC0A6CAB61D,
        0x46666F83085577F7, 0x1C9C490D221B73DC, 0xDEA491F6F6EE802C, 0x1B9DCB693897492, 0x3EA28ABBBDFFD145, 0x13E30E3BE0C89052,
        0xE4CE5E55AF602D8, 0xE1990F4F68CB3E67, 0x542ADA8D5527D266, 0x34673E84E834D65E, 0xB59696AF785BDB05, 0xE0291C97B936E698,
        0xEEF2B5745DE17AFE, 0x14D79D19DE099C79, 0x2F273341A852E4A1, 0xA7B5FA320543AB95, 0x588E85B34A59AD16, 0x7E4529E41D51B786,
        0x32CEE510B0A1BDE1, 0x6A7098A57C46B1F9, 0x5774F4E647E31FCE, 0x4B28C14499302DE6, 0x6CB272271CAD04EE, 0x608135ABE4095CC0,
        0xE99ED71E6BA46FB2, 0xF1EC572B77EABF00, 0xA08C8A0EB9B9DE57, 0x2208205645146F8D, 0xB6482B2385F1DDAB, 0xD221F3646AD755CA,
        0x4C635F8A3F03B407, 0x8C7110987AF22499, 0x524AEDD5BF72B6B7, 0xC27966DD82A7363F, 0x4F7EA4FA30F32EE3, 0x554D858294EDBAFE,
        0x9594C65372B24C82, 0xCCCA2F419C4B8936, 0xD45F890D0BCC31EA, 0xF8F7B1AB9EE0A721, 0x179A443DC477BBFE, 0xB953345332C7C009,
        0x475634E60BC116D1, 0x2A296C565321BCE1, 0xEF717FF243FD94F1, 0x594848422B6711E3, 0xC9DC91DB91A21E1E, 0xAE25A011874D951E,
        0x6061EA659AC0C854, 0xB664948925CA62B6, 0x9AFF64EE4E61022E, 0xC33043668F428EE3, 0x4EB2EA16135508E2, 0x65E65049F1E89B3,
        0x4AC49E90470C9A04, 0xC014D2067BA245A1, 0x828C710AA27FC949, 0xBFC3314B924A4C4E, 0xF9648C12946545B0, 0x4063C67750EEA39F,
        0xEE4F0E3184A39AD8, 0x62479EE2F4645571, 0x2FC2F31A2B0CCE38, 0xE25F210BCB27345B, 0x34DEEC68161785CD, 0x310A66AA08D3D8AE,
        0xAB24077BC99E5786, 0x8F11B422FABDF035, 0x50EC7548A39C3868, 0x9A6AFA4488423222, 0x95D73811B0378CD1, 0xB6FF585D68D73799,
        0xFBC78831EC3B001B, 0x7AF77D030C0D146B, 0x6F07B7E0C27203E8, 0x31D534B5960CFA88, 0x8F66A1C42DDF89A9, 0x5381E80F6C8CC552,
        0x822878E0863B3219, 0x747E4C9996466B94, 0x1F912901878FCAEB, 0xA11636C36E35E41, 0x81C25E6ECA32A443, 0xA81C94FDC04B85AC,
        0x5B3D13049E6B3DD, 0x41E4CDA51E75584E, 0x50705FEF2DB0480C, 0x5C31382FD799A709, 0xC644CD687F3D96F8, 0xFB987672A10B6CD4,
        0xAC49AAA6D65CAF63, 0x4DB52584D4B594BF, 0x122EEA4FA2C9A3FE, 0xED2ECB18DAEC0A1A, 0x50B2912C88C0B2DB };

        for(int i=0;i<521;i++) fRandF[i] = dRandF[i] + (seed*997);
        posRandF = 519;
}

unsigned long long generateRandF()
{
    posRandF++;
    fRandF[posRandF%521] = (fRandF[(posRandF-bRandF+1)%521] ^ fRandF[(posRandF-aRandF+1)%521]);
    return fRandF[posRandF%521]%1000;
}

//-----------------------------------------------MAIN CODE-----------------------------------------------------//

char board[20][20], lastWent;
int onGoing, ate, score;
double targetTime;

void timingThings(clock_t *timeS);

struct SnakeS{
    struct BodyS{
        int y[402];
        int x[402];
    }body;
    int blt;
}snake;

void stop(){
    onGoing=0;
    if(score>=200)
        printf("\n\tWow.....that's an impressive score!");
    Sleep(750);
}

void showme(){
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    int snakePrinted=0;
    printf("\t\tScore: %d", score);
    printf("\n.");
    for(int i=0;i<40;i++)
        printf("-");
    printf(".\n");
    for(int i=0;i<20;i++){
        printf("|");
        for(int j=0; j<20; j++){
            for(int k=0; k<snake.blt; k++)
                if(snake.body.y[k]==i && snake.body.x[k]==j){
                    if(snake.body.y[snake.blt-1]==i && snake.body.x[snake.blt-1]==j)
                        board[i][j]='O';
                    else board[i][j]='X';
                    snakePrinted=1;
                    break;
                }
            if(!snakePrinted && board[i][j]!='F'){
                board[i][j]=' ';
            }
            else snakePrinted=0;
            printf(" %c", board[i][j]);
        }
        printf("|\n");
    }
    printf("'");
    for(int i=0;i<40;i++)
        printf("-");
    printf("'\n");
}

int fruitEaten(){
    if(board[snake.body.y[snake.blt-1]][snake.body.x[snake.blt-1]]=='F'){
        board[snake.body.y[snake.blt-1]][snake.body.x[snake.blt-1]]=' ';
        return 1;
    }
    else return 0;
}

void moveTheRest(){
    if(snake.blt>1){
        for(int i=0; i<snake.blt-1; i++){
            snake.body.y[i]=snake.body.y[i+1];
            snake.body.x[i]=snake.body.x[i+1];
        }
    }
}

void checkCollision(int sposy, int sposx){
    for(int i=0; i<snake.blt; i++){
        if(snake.body.x[i]==sposx && snake.body.y[i]==sposy && i!=0){
            printf("\nYou lost the game by eating yourself with Score: %d. Better luck next time!", score);
            stop();
        }
    }
}

void walled(){
    printf("\nYou bashed your head in a wall and lost the game with a Score of %d!", score);
    stop();
}

void direction(char dir){
    switch (dir)
    {
        case 'W':
        case 'w':
            if(snake.body.y[snake.blt-1]-1!=snake.body.y[snake.blt-2])
                lastWent='W';
            break;
        case 'A':
        case 'a':
            if(snake.body.x[snake.blt-1]-1!=snake.body.x[snake.blt-2])
                lastWent='A';
            break;
        case 'S':
        case 's':
            if(snake.body.y[snake.blt-1]+1!=snake.body.y[snake.blt-2])
                lastWent='S';
            break;
        case 'D':
        case 'd':
            if(snake.body.x[snake.blt-1]+1!=snake.body.x[snake.blt-2])
                lastWent='D';
            break;
    }
}

void goDirection(char dir)
{
    switch (dir)
    {
        case 'W':
        case 'w':
            if (snake.body.y[snake.blt-1] > 0){
                if(snake.blt>1){
                    checkCollision(snake.body.y[snake.blt-1]-1, snake.body.x[snake.blt-1]);
                    moveTheRest();
                    snake.body.y[snake.blt-1]--;
                }else snake.body.y[snake.blt-1]--;
            }else walled();
            break;
        case 'A':
        case 'a':
            if (snake.body.x[snake.blt-1] > 0){
                if(snake.blt>1){
                    checkCollision(snake.body.y[snake.blt-1], snake.body.x[snake.blt-1]-1);
                    moveTheRest();
                    snake.body.x[snake.blt-1]--;
                }else snake.body.x[snake.blt-1]--;
            }else walled();
            break;
        case 'S':
        case 's':
            if (snake.body.y[snake.blt-1] < 19){
                if(snake.blt>1){
                    checkCollision(snake.body.y[snake.blt-1]+1, snake.body.x[snake.blt-1]);
                    moveTheRest();
                    snake.body.y[snake.blt-1]++;
                }else snake.body.y[snake.blt-1]++;
            }else walled();
            break;
        case 'D':
        case 'd':
            if (snake.body.x[snake.blt-1] < 19){
                if(snake.blt>1){
                    checkCollision(snake.body.y[snake.blt-1], snake.body.x[snake.blt-1]+1);
                    moveTheRest();
                    snake.body.x[snake.blt-1]++;
                }else snake.body.x[snake.blt-1]++;
            }else walled();
            break;
    }
    if(targetTime>0.3)
        targetTime-=0.01;
    else if(targetTime>0.13)
        targetTime-=0.0008;
    else if(targetTime>0.05)
        targetTime-=0.0003;
    if(fruitEaten()==1){
        ate=1;
    }
    showme();
}

void addSnake(){
    for(int i=snake.blt; i>0; i--){
        snake.body.x[i]=snake.body.x[i-1];
        snake.body.y[i]=snake.body.y[i-1];
    }
    snake.body.x[0]=snake.body.x[1];
    snake.body.y[0]=snake.body.y[1];
    snake.blt++;
    score+=1/targetTime;
}

void keyInput(clock_t *timeS)
{
    if (kbhit())
    {
        char chkb = getch();
        int tempchkb = (int)chkb;
        if (tempchkb == 27)
        {
            printf("\nGame Exited with Score: %d. We already miss you!", score);
            stop();
        }
        else if(tempchkb==119 || tempchkb==97 || tempchkb==115 || tempchkb==100 || tempchkb==87 || tempchkb==65 || tempchkb==83 || tempchkb==68)
        {
            if(chkb!=lastWent){
                direction(chkb);
            }
            timingThings(timeS);
        }
    }
}

void timingThings(clock_t *timeS){
    while ((clock() - *timeS) < targetTime*1000 && onGoing==1 && ate==0)
    {
        keyInput(timeS);
    }
}

void foodRand(){
    int foodposx, foodposy;
    do{
        foodposx=generateRandF()%20;
        foodposy=generateRandF()%20;
    }while(board[foodposy][foodposx]!=' ');
    board[foodposy][foodposx]='F';
}

void startGame(){
    initRandF(time(NULL));

    clock_t timeS, pizzaTime;

    int targetTimePizza=3.3, ignoredFood=0;
    score=0;
    onGoing=1;
    targetTime=0.3;
    snake.blt=0;
    lastWent='W';
    snake.body.x[0]=10;
    snake.body.y[0]=10;
    snake.blt=1;

    system("cls");
    for(int i=0; i<20; i++){
        for(int j=0; j<20; j++){
            board[i][j]=' ';
        }
    }

    foodRand();
    showme();
    pizzaTime=clock();

    while(onGoing==1){
        ate=0;
        int dontEat=0;
        while ((clock() - pizzaTime) < targetTimePizza*1000 && onGoing==1 && ate==0)
        {
            timeS = clock();
            timingThings(&timeS);
            if(ate==0 && onGoing==1)
                goDirection(lastWent);
            else break;
        }
        if(!ate && onGoing){
            ignoredFood++;
            foodRand();
            pizzaTime=clock();
            showme();
            if(ignoredFood>=9){
                printf("\nWhoops, it seems you ignored 10 consecutive foods and the snake starved to death with a Score of %d!", score);
                stop();
            }
        }else if(onGoing==1){
            for(int i=0; i<20; i++)
                for(int j=0; j<20; j++)
                    if(board[i][j]=='F'){
                        dontEat=1;
                        break;
                    }
            if(!dontEat)
                foodRand();
            ignoredFood--;
            addSnake();

            showme();
        }
    }

    printf("\n\n\n\tDo you want to play again? Press ENTER. Otherwise press ESC:");
    char scn;
    while(1){//this was done to prevent missclicks after the game was finished in case it was very sudden.
        scn=getch();
        if((int)scn==13){
            startGame();
            break;
        }
        else if((int)scn==27){
            printf("\n\nThank you for playing, bye! <3");
            break;
        }
    }
}

int main(){
    startGame();
}
