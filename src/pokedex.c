#include "global.h"
#include "constants/bg_music.h"
#include "functions.h"
#include "m4a.h"
#include "main.h"
#include "types.h"
#include "variables.h"

void sub_4F50(void);
void sub_5174(void);
void sub_4EF0(void);
void sub_4E34(void);
void sub_4D74(void);
void sub_4FC8(void);
void sub_5064(void);
void sub_51CC(void);
void sub_70E0(s16, s32);
void sub_88E4(void);

void PokedexMain(void)
{
    gPokedexStateFuncs[gMain.subState]();
}

void LoadPokedexGraphics(void)
{
    ResetSomeGraphicsRelatedStuff();
    
    REG_DISPCNT = DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_FORCED_BLANK | DISPCNT_OBJ_ON;
    REG_BG1CNT = BGCNT_PRIORITY(1) | BGCNT_CHARBASE(1) | BGCNT_16COLOR | BGCNT_SCREENBASE(0) | BGCNT_TXT256x256;
    REG_DISPCNT |= DISPCNT_BG1_ON;
    REG_BG2CNT = BGCNT_PRIORITY(2) | BGCNT_CHARBASE(3) | BGCNT_16COLOR | BGCNT_SCREENBASE(1) | BGCNT_TXT256x256;
    REG_DISPCNT |= DISPCNT_BG2_ON;
    REG_BG3CNT = BGCNT_PRIORITY(3) | BGCNT_CHARBASE(3) | BGCNT_16COLOR | BGCNT_SCREENBASE(2) | BGCNT_TXT256x256;
    REG_DISPCNT |= DISPCNT_BG3_ON;
    
    gMain.unk16 = REG_DISPCNT;
    
    DmaCopy16(3, gUnknown_08082720, (void *)BG_CHAR_ADDR(1), 0x4400);
    DmaCopy16(3, gUnknown_08087B40, (void *)BG_CHAR_ADDR(3), 0x1400);
    DmaCopy16(3, gUnknown_08089760, (void *)BG_PLTT, BG_PLTT_SIZE);
    DmaCopy16(3, gUnknown_08081F20, gUnknown_03005C00, BG_SCREEN_SIZE);
    DmaCopy16(3, gUnknown_08087340, gUnknown_02019C40, BG_SCREEN_SIZE);
    DmaCopy16(3, gUnknown_08088F60, (void *)BG_SCREEN_ADDR(2), BG_SCREEN_SIZE);
    DmaCopy16(3, gUnknown_08089960, (void *)OBJ_PLTT, OBJ_PLTT_SIZE);
    DmaCopy16(3, gUnknown_08089B60, (void *)OBJ_VRAM0, 0x6C20);
    
    sub_3FAC();
    sub_6BEC(gUnknown_0202BEB8, gUnknown_0201A514);
    sub_681C(gUnknown_0202ADE0);
    sub_6CA0(gUnknown_0202C5B0);
    sub_6F30(gUnknown_0202C5B0);
    sub_6F78(gUnknown_0202ADE0);
    sub_8974(gUnknown_0202ADE0);
    sub_8A78(gUnknown_0202ADE0);
    
    gUnknown_02019C40[0x134] = 0x59;
    
    DmaCopy16(3, gUnknown_03005C00, (void *)BG_SCREEN_ADDR(0), BG_SCREEN_SIZE);
    DmaCopy16(3, gUnknown_02019C40, (void *)BG_SCREEN_ADDR(1), BG_SCREEN_SIZE);
    
    sub_51FC();
    sub_0CBC();
    sub_024C();
    
    // Must be `= 1` to match, cannot be `++`
    gMain.subState = 1;
    
    m4aSongNumStart(MUS_POKEDEX);
}

void sub_3FAC(void) {
    s32 i;
    
    gUnknown_0202ADE0 = 0;
    gUnknown_0202C5B0 = 0;
    gUnknown_0201A448 = 0;
    gUnknown_0202BF00 = 0;
    gUnknown_0202A57C = 0;
    gUnknown_0201A4F0 = 0;
    gUnknown_0202BE20 = 0;
    gUnknown_0202C58C = 0;
    gUnknown_02019C24 = 0;
    gUnknown_0202BF0C = 0;
    gUnknown_0201A440 = 0;
    gUnknown_0202C5E8 = 0;
    gUnknown_0202BEF4 = 0;
    gUnknown_0202A588 = 1;
    gUnknown_0202A55C = 1;
    
    gUnknown_0202A568[0] = 0;
    gUnknown_0202A568[1] = 0;
    
    gUnknown_0202BF14 = 0;
    gUnknown_0202A558 = 0;
    gUnknown_0202BEE0 = 0;
    gUnknown_0202BF04 = 1;

    sub_88E4();
    if (sub_FD20() == 1)
    {
        gUnknown_0202C590 = 1;
    }
    else
    {
        gUnknown_0202C590 = 0;
    }

    gUnknown_0202BEC4 = 0;
    gUnknown_0202BEFC = 0;
    gUnknown_0201B120 = 0;
    gUnknown_02002830 = 0;
    gUnknown_02002831 = 0;
    gUnknown_0202C794 = 0;
    gUnknown_0201C1B4 = 0;
    gUnknown_0202C5AC = 0;
    gUnknown_02019C28 = 0;

    for (i = 0; i < 0xE1; i++)
    {
        gUnknown_0202A390[i] = gUnknown_0202A1C0[i];
    }

    if (gUnknown_0202A1C0[SPECIES_AERODACTYL])
    {
        gUnknown_0202A574 = SPECIES_AERODACTYL + 1;
    }
    else if (gUnknown_0202A1C0[SPECIES_TOTODILE])
    {
        gUnknown_0202A574 = SPECIES_TOTODILE + 1;
    }
    else if (gUnknown_0202A1C0[SPECIES_CYNDAQUIL])
    {
        gUnknown_0202A574 = SPECIES_CYNDAQUIL + 1;
    }
    else if (gUnknown_0202A1C0[SPECIES_CHIKORITA])
    {
        gUnknown_0202A574 = SPECIES_CHIKORITA + 1;
    }
    else if (gUnknown_0202A1C0[SPECIES_JIRACHI])
    {
        gUnknown_0202A574 = SPECIES_JIRACHI + 1;
    }
    else
    {
        gUnknown_0202A574 = SPECIES_RAYQUAZA + 1;
    }
}

void sub_4150(void) {
    if (gMain.heldKeys & SELECT_BUTTON)
    {
        gUnknown_0202BF04 = 0;

        if (gMain.heldKeys & DPAD_UP)
        {
            sub_4D74();
            sub_5064();
            sub_51CC();
            gMain.subState = 2;
        }
        else if (gMain.heldKeys & DPAD_DOWN)
        {
            sub_4E34();
            sub_5064();
            sub_51CC();
            gMain.subState = 2;
        }
        else if (gMain.heldKeys & DPAD_LEFT)
        {
            sub_4EF0();
            sub_5064();
            sub_51CC();
            gMain.subState = 2;
        }
        else if (gMain.heldKeys & DPAD_RIGHT)
        {
            sub_4F50();
            sub_5064();
            sub_51CC();
            gMain.subState = 2;
        }
        else
        {
            gUnknown_02019C24 = 0;
            sub_5064();
        }

        if (gMain.newKeys & A_BUTTON)
        {
            gUnknown_0202C5E8 = 0;

            if (gUnknown_0202A1C0[gUnknown_0202ADE0] >= 2)
            {
                gUnknown_0202BF04 = 0;
                DmaCopy16(3, 0x6000280, (void *)gUnknown_0202A590, 0x200);
                gMain.subState = 3;
            }
            else
            {
                m4aSongNumStart(0x8A);
            }
        }
    }
    else
    {
        gUnknown_0202BF04 = 1;

        if (gMain.heldKeys & DPAD_UP)
        {
            sub_4D74();
            sub_5174();
        }
        else if (gMain.heldKeys & DPAD_DOWN)
        {
            sub_4E34();
            sub_5174();
        }
        else if (gMain.heldKeys & DPAD_LEFT)
        {
            sub_4EF0();
            sub_5174();
        }
        else if (gMain.heldKeys & DPAD_RIGHT)
        {
            sub_4F50();
            sub_5174();
        }
        else
        {
            gUnknown_02019C24 = 0;
        }

        if (sub_8A78(gUnknown_0202ADE0) == 1)
        {
            gUnknown_0202A588 = 1;
        }
        else
        {
            gUnknown_0202A588 = 0;
        }

        gUnknown_0202A55C = 1;
        gUnknown_0202A568[0] = 0;
        gUnknown_0202A568[1] = 0;
        gUnknown_0201A440 = 0;
        gUnknown_0202BF0C = 0;

        if (gMain.newKeys & A_BUTTON)
        {
            gUnknown_0202C5E8 = 0;

            if (gUnknown_0202A1C0[gUnknown_0202ADE0] >= 2)
            {
                gUnknown_0202BF04 = 0;
                DmaCopy16(3, 0x6000280, (void *)gUnknown_0202A590, 0x200);
                gMain.subState = 3;
            }
            else
            {
                m4aSongNumStart(0x8A);
            }
        }
        else if (gMain.newKeys & B_BUTTON)
        {
            m4aSongNumStart(0x66);
            gMain.subState = 12;
        }
        else if (gMain.newKeys & START_BUTTON)
        {
            m4aSongNumStart(0x68);
            gUnknown_0202BEC4 = 1;
            gUnknown_0202BEFC = 0;
            gUnknown_0202BF04 = 0;
            gUnknown_0202A588 = 0;
            gMain.subState = 6;
        }

        sub_4FC8();
    }

    if (gUnknown_0202C58C > 0)
    {
        gUnknown_0202C58C--;
    }

    sub_51FC();
    DmaCopy16(3, gUnknown_03005C00, (void *)BG_SCREEN_ADDR(0), BG_SCREEN_SIZE);
}

void sub_43D4(void) {
    sub_5174();
    gUnknown_0202A588 = 0;

    if (gUnknown_0202C58C > 0)
    {
        gUnknown_0202C58C--;
    }

    sub_51FC();
    DmaCopy16(3, gUnknown_03005C00, (void *)BG_SCREEN_ADDR(0), BG_SCREEN_SIZE);
    gMain.subState = 1;
}

void sub_4428(void) {
    s32 i;

    for (i = 0; i < 0x20; i++)
    {
        gUnknown_03005C00[0x20*(gUnknown_0202A558 + 10) + i] = gUnknown_0805C840[i];
        gUnknown_02019C40[0x20*(gUnknown_0202A558 + 9) + i] = gUnknown_0805C780[i];
        gUnknown_02019C40[0x20*(gUnknown_0202A558 + 10) + i] = gUnknown_0805C7C0[i];
    }
    
    gUnknown_0202A558++;
    gUnknown_02019C40[0x134] = 0x59;
    DmaCopy16(3, gUnknown_03005C00, (void *)BG_SCREEN_ADDR(0), BG_SCREEN_SIZE);
    DmaCopy16(3, gUnknown_02019C40, (void *)BG_SCREEN_ADDR(1), BG_SCREEN_SIZE);

    if (gUnknown_0202A558 > 7)
    {
        gUnknown_0202A558 = 0;
        gUnknown_0202C5E8 = 0;
        gUnknown_0202BEF4 = 0;
        gUnknown_02019C28 = 0;
        gUnknown_0202C5AC = 0;

        if (gUnknown_0202ADE0 < BONUS_SPECIES_START) {
            gUnknown_0201C1B4 = 1;
        }

        DmaCopy16(3, gUnknown_08086B40, (void *)0x6000280, 2*0xE0);
        sub_70E0(gUnknown_0202ADE0, gUnknown_0202C794);
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, TRACKS_ALL, 0x40);
        sub_5291C(gUnknown_086A3700[gUnknown_0202ADE0].mainSeriesIndexNumber, 0, 0x7F, 10);
        gMain.subState = 5;
    }
    
}

void sub_45A4(void) {
    u16 var0;
    
    if (gUnknown_0202C5E8 < 0x51)
    {
        gUnknown_0202C5E8++;
        if (gUnknown_0202C5E8 == 0x50)
        {
            m4aMPlayVolumeControl(&gMPlayInfo_BGM, TRACKS_ALL, 0x100);
        }
    }
    gUnknown_0202BEF4 = gUnknown_0202BEF4 + 1;
    if (0x1e < gUnknown_0202BEF4)
    {
        gUnknown_0202BEF4 = 0;
        gUnknown_0202C5AC = 1 - gUnknown_0202C5AC;
    }
    gUnknown_0202BE20 = 0;

    if (gMain.newKeys & DPAD_UP)
    {
        if ((gUnknown_0202ADE0 < BONUS_SPECIES_START) && (gUnknown_0202C794 == 1))
        {
            m4aSongNumStart(0x6D);
            gUnknown_0202C794 = 0;
            sub_70E0(gUnknown_0202ADE0, 0);
            gUnknown_02019C28 = gUnknown_0202C794;
        }
    }
    else if (gMain.newKeys & DPAD_DOWN)
    {
        if ((gUnknown_0202ADE0 < BONUS_SPECIES_START) && (gUnknown_0202C794 == 0))
        {
            m4aSongNumStart(0x6D);
            gUnknown_0202C794 = 1;
            sub_70E0(gUnknown_0202ADE0, 1);
            gUnknown_02019C28 = gUnknown_0202C794;
        }
    }
    
    if (gMain.newKeys & A_BUTTON)
    {
        if (gUnknown_0202ADE0 < BONUS_SPECIES_START)
        {
            if (!gUnknown_0202C794)
            {
                m4aSongNumStart(0x6D);
                gUnknown_0202C794 = 1 - gUnknown_0202C794;
                sub_70E0(gUnknown_0202ADE0,gUnknown_0202C794);
                gUnknown_02019C28 = gUnknown_0202C794;
            }
            else
            {
                m4aSongNumStart(0x69);
                m4aMPlayVolumeControl(&gMPlayInfo_BGM, TRACKS_ALL, 0x100);
                gUnknown_0202C794 = 0;
                gUnknown_0202C5E8 = 0;
                gUnknown_0202BEF4 = gUnknown_0202C5E8;
                gUnknown_0201C1B4 = 0;
                gMain.subState = 4;
            }
        }
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        m4aSongNumStart(0x69);
        m4aMPlayVolumeControl(&gMPlayInfo_BGM, TRACKS_ALL, 0x100);
        gUnknown_0202C794 = 0;
        gUnknown_0202C5E8 = 0;
        gUnknown_0202BEF4 = gUnknown_0202C5E8;
        gUnknown_0201C1B4 = 0;
        gMain.subState = 4;
    }

    if (gMain.heldKeys & SELECT_BUTTON)
    {
        if (gUnknown_0202A1C0[gUnknown_0202ADE0] == 4)
        {
            if (gUnknown_086A61BC[gUnknown_0202ADE0] == -1)
            {
                gUnknown_0202A588 = 0;
                gUnknown_0202A55C = 1;
                gUnknown_0202A568[0] = 0;
                gUnknown_0202A568[1] = 0;
                gUnknown_0201A440 = 0;
                gUnknown_0202BF0C = 0;
            }
            else
            {
                if (gUnknown_086A61BC[gUnknown_0202ADE0] < 100)
                {
                    gUnknown_0202A588 = 0;
                    gUnknown_0202A55C = 0;
                    gUnknown_0202A568[0] = 1;
                    gUnknown_0202A568[1] = 0;
                }
                else
                {
                    gUnknown_0202A588 = 0;
                    gUnknown_0202A55C = 0;
                    gUnknown_0202A568[0] = 0;
                    gUnknown_0202A568[1] = 1;
                }
            }
        }
        else
        {
            gUnknown_0202A588 = 0;
            gUnknown_0202A55C = 1;
            gUnknown_0202A568[0] = 0;
            gUnknown_0202A568[1] = 0;
        }
    }
    else
    {
        if (sub_8A78(gUnknown_0202ADE0) == 1)
        {
            gUnknown_0202A588 = 1;
        }
        else
        {
            gUnknown_0202A588 = 0;
        }

        gUnknown_0202A55C = 1;
        gUnknown_0202A568[0] = 0;
        gUnknown_0202A568[1] = 0;
        gUnknown_0201A440 = 0;
        gUnknown_0202BF0C = 0;
    }

    sub_51FC();
}
