#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

namespace UI {

    enum class Fonts {
        Autoradiographic_Rg_It,
        Autoradiographic_Rg,
        Axaxax_Bd,
        Bench_Grinder_Titling,
        Bitcrusher_Condensed_Bd,
        Breamcatcher_Rg,
        Budmo_Jiggler,
        Budmo_Jigglish,
        Built_Titling_Bd_It,
        Built_Titling_Bd,
        Built_Titling_El_It,
        Built_Titling_El,
        Built_Titling_Lt_It,
        Built_Titling_Lt,
        Built_Titling_Rg_It,
        Built_Titling_Rg,
        Built_Titling_Sb_It,
        Built_Titling_Sb,
        Bullpen_3D,
        Bullpen_Hv_It,
        Bullpen_Hv,
        Carbon_Bl,
        Carbon_Phyber,
        Cardigan_Titling_Bd_It,
        Cardigan_Titling_Bd,
        Cardigan_Titling_It,
        Cardigan_Titling_Rg,
        Cardigan_Titling_Sb_It,
        Cardigan_Titling_Sb,
        Chickweed_Titling,
        Chinese_Rocks_Rg,
        Conthrax_SemiBold,
        Coolvetica_Hv_Comp,
        Coolvetica_Rg_Cond,
        Coolvetica_Rg_Cram,
        Coolvetica_Rg_It,
        Coolvetica_Rg,
        Dealerplate_California,
        Densmore,
        Dirty_Bakers_Dozen,
        Dream_Orphanage_Rg,
        Duality,
        Earwig_Factory_Rg,
        Ethnocentric_Rg_It,
        Ethnocentric_Rg,
        Evensong_Hollow,
        Expressway_Rg,
        Fenwick_Outline,
        Fledgling_Sb,
        Forgotten_Futurist_Bd_It,
        Forgotten_Futurist_Bd,
        Forgotten_Futurist_Rg_It,
        Forgotten_Futurist_Rg,
        Galderglynn_Titling_Bd_It,
        Galderglynn_Titling_Bd,
        Galderglynn_Titling_Bl_It,
        Galderglynn_Titling_Bl,
        Galderglynn_Titling_El_It,
        Galderglynn_Titling_El,
        Galderglynn_Titling_Hl_It,
        Galderglynn_Titling_Hl,
        Galderglynn_Titling_Lt_It,
        Galderglynn_Titling_Lt,
        Galderglynn_Titling_Rg_It,
        Galderglynn_Titling_Rg,
        Galderglynn_Titling_Th_It,
        Galderglynn_Titling_Th,
        Geoparody_Hv,
        Geoparody_Rg,
        Gnuolane_Rg,
        Good_Times_Rg,
        Good_Timing_Bd,
        Gravtrac_Bd_Comp,
        Gunplay_3D,
        Gunplay_Rg,
        Gymkhana_Lt,
        Heavy_Heap_Rg,
        Hemi_Head_Bd_It,
        Jesaya_Lt,
        Joystix_Monospace,
        Junegull_Rg,
        Kenyan_Coffee_Bd_It,
        Kenyan_Coffee_Bd,
        Kenyan_Coffee_Rg_It,
        Kenyan_Coffee_Rg,
        Kenyan_Coffee_Stencil_Sb,
        Kimberley_Bl,
        Kingsbridge_Bd_It,
        Kingsbridge_Bd,
        Kingsbridge_Bk_It,
        Kingsbridge_Bk,
        Kingsbridge_Cd_Bd_It,
        Kingsbridge_Cd_Bd,
        Kingsbridge_Cd_Bk_It,
        Kingsbridge_Cd_Bk,
        Kingsbridge_Cd_El_It,
        Kingsbridge_Cd_El,
        Kingsbridge_Cd_Lt_It,
        Kingsbridge_Cd_Lt,
        Kingsbridge_Cd_Rg_It,
        Kingsbridge_Cd_Rg,
        Kingsbridge_Cd_Sb_It,
        Kingsbridge_Cd_Sb,
        Kingsbridge_Cd_Ul_It,
        Kingsbridge_Cd_Ul,
        Kingsbridge_El_It,
        Kingsbridge_El,
        Kingsbridge_Ex_Bd_It,
        Kingsbridge_Ex_Bd,
        Kingsbridge_Ex_Bk_It,
        Kingsbridge_Ex_Bk,
        Kingsbridge_Ex_El_It,
        Kingsbridge_Ex_El,
        Kingsbridge_Ex_Lt_It,
        Kingsbridge_Ex_Lt,
        Kingsbridge_Ex_Rg_It,
        Kingsbridge_Ex_Rg,
        Kingsbridge_Ex_Sb_It,
        Kingsbridge_Ex_Sb,
        Kingsbridge_Ex_Ul_It,
        Kingsbridge_Ex_Ul,
        Kingsbridge_Lt_It,
        Kingsbridge_Lt,
        Kingsbridge_Rg_It,
        Kingsbridge_Rg,
        Kingsbridge_Sb_It,
        Kingsbridge_Sb,
        Kingsbridge_Sc_Bd_It,
        Kingsbridge_Sc_Bd,
        Kingsbridge_Sc_Bk_It,
        Kingsbridge_Sc_Bk,
        Kingsbridge_Sc_El_It,
        Kingsbridge_Sc_El,
        Kingsbridge_Sc_Lt_It,
        Kingsbridge_Sc_Lt,
        Kingsbridge_Sc_Rg_It,
        Kingsbridge_Sc_Rg,
        Kingsbridge_Sc_Sb_It,
        Kingsbridge_Sc_Sb,
        Kingsbridge_Sc_Ul_It,
        Kingsbridge_Sc_Ul,
        Kingsbridge_Ul_It,
        Kingsbridge_Ul,
        Kirsty_Bd_It,
        Kirsty_Bd,
        Kirsty_Rg_It,
        Kirsty_Rg,
        Kleptocracy_Titling_Bd,
        Kleptocracy_Titling_Cd_Bd,
        Kleptocracy_Titling_Cd_Lt,
        Kleptocracy_Titling_Cd_Rg,
        Kleptocracy_Titling_Ex_Bd,
        Kleptocracy_Titling_Ex_Lt,
        Kleptocracy_Titling_Ex_Rg,
        Kleptocracy_Titling_Lt,
        Kleptocracy_Titling_Rg,
        Larabiefont_Rg,
        Libel_Suit_Suit_Rg,
        Meloche_Lt,
        Mexcellent_3D,
        Mexcellent_Rg,
        Mixolydian_Titling_Bd_It,
        Mixolydian_Titling_Bd,
        Mixolydian_Titling_El_It,
        Mixolydian_Titling_El,
        Mixolydian_Titling_Hl_It,
        Mixolydian_Titling_Hl,
        Mixolydian_Titling_Lt_It,
        Mixolydian_Titling_Lt,
        Mixolydian_Titling_Rg_It,
        Mixolydian_Titling_Rg,
        Mixolydian_Titling_Th_It,
        Mixolydian_Titling_Th,
        Monofonto_Rg,
        Mufferaw_Rg,
        Nasalization_Rg,
        Negotiate_Rg,
        Neuropol_X_Rg,
        Neuropolitical_Rg,
        Nulshock_Bd,
        Octin_College_Rg,
        Octin_Prison_Rg,
        Octin_Sports_Rg,
        Octin_Spraypaint_A_Rg,
        Octin_Stencil_Rg,
        Octin_Vintage_B_Rg,
        Pakenham_Rg,
        Palamecia_Titling,
        Pirulen_Rg,
        Pricedown_Bl,
        Pupcat_Rg,
        Quasix_Titling,
        Rakesly_Bd_It,
        Rakesly_Bd,
        Rakesly_El_It,
        Rakesly_El,
        Rakesly_Hl_It,
        Rakesly_Hl,
        Rakesly_Lt_It,
        Rakesly_Lt,
        Rakesly_Rg_It,
        Rakesly_Rg,
        Rakesly_Th_It,
        Rakesly_Th,
        Recharge_Bd,
        Remissis_Sb,
        Rexlia_Rg,
        Rimouski_Sb,
        Shlop_Rg,
        Sofachrome_Rg_It,
        Sofachrome_Rg,
        Steelfish_Bd_It,
        Steelfish_Bd,
        Steelfish_Eb_It,
        Steelfish_Eb,
        Steelfish_Outline,
        Steelfish_Rg_It,
        Steelfish_Rg,
        Steelfish_Rounded_Bd,
        Strenuous_3D,
        Strenuous_Bl,
        Sui_Generis_Rg,
        Toxigenesis_Bd,
        Venus_Rising_Rg,
        Vinque_Rg,
        Vipnagorgialla_Bd_It,
        Vipnagorgialla_Bd,
        Vipnagorgialla_Rg_It,
        Vipnagorgialla_Rg,
        Wheaton_Capitals,
        Zekton_Rg,
        Zrnic_Rg
    };

    class Font {
    public:
        Fonts font;

        Font(Fonts f) : font(f) {}
        
        static std::string FontToString(Fonts f) {
            switch (f) {
            case Fonts::Autoradiographic_Rg_It: return "Cache/Fonts/autoradiographic rg it.otf";
            case Fonts::Autoradiographic_Rg: return "Cache/Fonts/autoradiographic rg.otf";
            case Fonts::Axaxax_Bd: return "Cache/Fonts/axaxax bd.otf";
            case Fonts::Bench_Grinder_Titling: return "Cache/Fonts/bench grinder titling.otf";
            case Fonts::Bitcrusher_Condensed_Bd: return "Cache/Fonts/bitcrusher condensed bd.otf";
            case Fonts::Breamcatcher_Rg: return "Cache/Fonts/breamcatcher rg.otf";
            case Fonts::Budmo_Jiggler: return "Cache/Fonts/budmo jiggler.otf";
            case Fonts::Budmo_Jigglish: return "Cache/Fonts/budmo jigglish.otf";
            case Fonts::Built_Titling_Bd_It: return "Cache/Fonts/built titling bd it.otf";
            case Fonts::Built_Titling_Bd: return "Cache/Fonts/built titling bd.otf";
            case Fonts::Built_Titling_El_It: return "Cache/Fonts/built titling el it.otf";
            case Fonts::Built_Titling_El: return "Cache/Fonts/built titling el.otf";
            case Fonts::Built_Titling_Lt_It: return "Cache/Fonts/built titling lt it.otf";
            case Fonts::Built_Titling_Lt: return "Cache/Fonts/built titling lt.otf";
            case Fonts::Built_Titling_Rg_It: return "Cache/Fonts/built titling rg it.otf";
            case Fonts::Built_Titling_Rg: return "Cache/Fonts/built titling rg.otf";
            case Fonts::Built_Titling_Sb_It: return "Cache/Fonts/built titling sb it.otf";
            case Fonts::Built_Titling_Sb: return "Cache/Fonts/built titling sb.otf";
            case Fonts::Bullpen_3D: return "Cache/Fonts/bullpen 3d.otf";
            case Fonts::Bullpen_Hv_It: return "Cache/Fonts/bullpen hv it.otf";
            case Fonts::Bullpen_Hv: return "Cache/Fonts/bullpen hv.otf";
            case Fonts::Carbon_Bl: return "Cache/Fonts/carbon bl.otf";
            case Fonts::Carbon_Phyber: return "Cache/Fonts/carbon phyber.otf";
            case Fonts::Cardigan_Titling_Bd_It: return "Cache/Fonts/Cardigan Titling Bd It.otf";
            case Fonts::Cardigan_Titling_Bd: return "Cache/Fonts/Cardigan Titling Bd.otf";
            case Fonts::Cardigan_Titling_It: return "Cache/Fonts/Cardigan Titling It.otf";
            case Fonts::Cardigan_Titling_Rg: return "Cache/Fonts/Cardigan Titling Rg.otf";
            case Fonts::Cardigan_Titling_Sb_It: return "Cache/Fonts/Cardigan Titling Sb It.otf";
            case Fonts::Cardigan_Titling_Sb: return "Cache/Fonts/Cardigan Titling Sb.otf";
            case Fonts::Chickweed_Titling: return "Cache/Fonts/chickweed titling.otf";
            case Fonts::Chinese_Rocks_Rg: return "Cache/Fonts/chinese rocks rg.otf";
            case Fonts::Conthrax_SemiBold: return "Cache/Fonts/Conthrax-SemiBold.otf";
            case Fonts::Coolvetica_Hv_Comp: return "Cache/Fonts/Coolvetica Hv Comp.otf";
            case Fonts::Coolvetica_Rg_Cond: return "Cache/Fonts/Coolvetica Rg Cond.otf";
            case Fonts::Coolvetica_Rg_Cram: return "Cache/Fonts/Coolvetica Rg Cram.otf";
            case Fonts::Coolvetica_Rg_It: return "Cache/Fonts/Coolvetica Rg It.otf";
            case Fonts::Coolvetica_Rg: return "Cache/Fonts/Coolvetica Rg.otf";
            case Fonts::Dealerplate_California: return "Cache/Fonts/dealerplate california.otf";
            case Fonts::Densmore: return "Cache/Fonts/densmore.otf";
            case Fonts::Dirty_Bakers_Dozen: return "Cache/Fonts/Dirty Bakers Dozen.otf";
            case Fonts::Dream_Orphanage_Rg: return "Cache/Fonts/dream orphanage rg.otf";
            case Fonts::Duality: return "Cache/Fonts/duality.otf";
            case Fonts::Earwig_Factory_Rg: return "Cache/Fonts/earwig factory rg.otf";
            case Fonts::Ethnocentric_Rg_It: return "Cache/Fonts/Ethnocentric Rg It.otf";
            case Fonts::Ethnocentric_Rg: return "Cache/Fonts/Ethnocentric Rg.otf";
            case Fonts::Evensong_Hollow: return "Cache/Fonts/evensong hollow.otf";
            case Fonts::Expressway_Rg: return "Cache/Fonts/expressway rg.otf";
            case Fonts::Fenwick_Outline: return "Cache/Fonts/Fenwick Outline.otf";
            case Fonts::Fledgling_Sb: return "Cache/Fonts/fledgling-sb.otf";
            case Fonts::Forgotten_Futurist_Bd_It: return "Cache/Fonts/Forgotten Futurist Bd It.otf";
            case Fonts::Forgotten_Futurist_Bd: return "Cache/Fonts/Forgotten Futurist Bd.otf";
            case Fonts::Forgotten_Futurist_Rg_It: return "Cache/Fonts/Forgotten Futurist Rg It.otf";
            case Fonts::Forgotten_Futurist_Rg: return "Cache/Fonts/Forgotten Futurist Rg.otf";
            case Fonts::Galderglynn_Titling_Bd_It: return "Cache/Fonts/Galderglynn Titling Bd It.otf";
            case Fonts::Galderglynn_Titling_Bd: return "Cache/Fonts/Galderglynn Titling Bd.otf";
            case Fonts::Galderglynn_Titling_Bl_It: return "Cache/Fonts/Galderglynn Titling Bl It.otf";
            case Fonts::Galderglynn_Titling_Bl: return "Cache/Fonts/Galderglynn Titling Bl.otf";
            case Fonts::Galderglynn_Titling_El_It: return "Cache/Fonts/Galderglynn Titling El It.otf";
            case Fonts::Galderglynn_Titling_El: return "Cache/Fonts/Galderglynn Titling El.otf";
            case Fonts::Galderglynn_Titling_Hl_It: return "Cache/Fonts/Galderglynn Titling Hl It.otf";
            case Fonts::Galderglynn_Titling_Hl: return "Cache/Fonts/Galderglynn Titling Hl.otf";
            case Fonts::Galderglynn_Titling_Lt_It: return "Cache/Fonts/Galderglynn Titling Lt It.otf";
            case Fonts::Galderglynn_Titling_Lt: return "Cache/Fonts/Galderglynn Titling Lt.otf";
            case Fonts::Galderglynn_Titling_Rg_It: return "Cache/Fonts/Galderglynn Titling Rg It.otf";
            case Fonts::Galderglynn_Titling_Rg: return "Cache/Fonts/Galderglynn Titling Rg.otf";
            case Fonts::Galderglynn_Titling_Th_It: return "Cache/Fonts/Galderglynn Titling Th It.otf";
            case Fonts::Galderglynn_Titling_Th: return "Cache/Fonts/Galderglynn Titling Th.otf";
            case Fonts::Geoparody_Hv: return "Cache/Fonts/Geoparody Hv.otf";
            case Fonts::Geoparody_Rg: return "Cache/Fonts/Geoparody Rg.otf";
            case Fonts::Gnuolane_Rg: return "Cache/Fonts/Gnuolane Rg.otf";
            case Fonts::Good_Times_Rg: return "Cache/Fonts/Good Times Rg.otf";
            case Fonts::Good_Timing_Bd: return "Cache/Fonts/good timing bd.otf";
            case Fonts::Gravtrac_Bd_Comp: return "Cache/Fonts/Gravtrac Bd Comp.otf";
            case Fonts::Gunplay_3D: return "Cache/Fonts/gunplay 3d.otf";
            case Fonts::Gunplay_Rg: return "Cache/Fonts/gunplay rg.otf";
            case Fonts::Gymkhana_Lt: return "Cache/Fonts/Gymkhana Lt.otf";
            case Fonts::Heavy_Heap_Rg: return "Cache/Fonts/heavy heap rg.otf";
            case Fonts::Hemi_Head_Bd_It: return "Cache/Fonts/Hemi Head Bd It.otf";
            case Fonts::Jesaya_Lt: return "Cache/Fonts/Jesaya Lt.otf";
            case Fonts::Joystix_Monospace: return "Cache/Fonts/joystix monospace.otf";
            case Fonts::Junegull_Rg: return "Cache/Fonts/junegull rg.otf";
            case Fonts::Kenyan_Coffee_Bd_It: return "Cache/Fonts/Kenyan Coffee Bd It.otf";
            case Fonts::Kenyan_Coffee_Bd: return "Cache/Fonts/Kenyan Coffee Bd.otf";
            case Fonts::Kenyan_Coffee_Rg_It: return "Cache/Fonts/Kenyan Coffee Rg It.otf";
            case Fonts::Kenyan_Coffee_Rg: return "Cache/Fonts/Kenyan Coffee Rg.otf";
            case Fonts::Kenyan_Coffee_Stencil_Sb: return "Cache/Fonts/Kenyan Coffee Stencil Sb.otf";
            case Fonts::Kimberley_Bl: return "Cache/Fonts/Kimberley Bl.otf";
            case Fonts::Kingsbridge_Bd_It: return "Cache/Fonts/kingsbridge bd it.otf";
            case Fonts::Kingsbridge_Bd: return "Cache/Fonts/kingsbridge bd.otf";
            case Fonts::Kingsbridge_Bk_It: return "Cache/Fonts/kingsbridge bk it.otf";
            case Fonts::Kingsbridge_Bk: return "Cache/Fonts/kingsbridge bk.otf";
            case Fonts::Kingsbridge_Cd_Bd_It: return "Cache/Fonts/kingsbridge cd bd it.otf";
            case Fonts::Kingsbridge_Cd_Bd: return "Cache/Fonts/kingsbridge cd bd.otf";
            case Fonts::Kingsbridge_Cd_Bk_It: return "Cache/Fonts/kingsbridge cd bk it.otf";
            case Fonts::Kingsbridge_Cd_Bk: return "Cache/Fonts/kingsbridge cd bk.otf";
            case Fonts::Kingsbridge_Cd_El_It: return "Cache/Fonts/kingsbridge cd el it.otf";
            case Fonts::Kingsbridge_Cd_El: return "Cache/Fonts/kingsbridge cd el.otf";
            case Fonts::Kingsbridge_Cd_Lt_It: return "Cache/Fonts/kingsbridge cd lt it.otf";
            case Fonts::Kingsbridge_Cd_Lt: return "Cache/Fonts/kingsbridge cd lt.otf";
            case Fonts::Kingsbridge_Cd_Rg_It: return "Cache/Fonts/kingsbridge cd rg it.otf";
            case Fonts::Kingsbridge_Cd_Rg: return "Cache/Fonts/kingsbridge cd rg.otf";
            case Fonts::Kingsbridge_Cd_Sb_It: return "Cache/Fonts/kingsbridge cd sb it.otf";
            case Fonts::Kingsbridge_Cd_Sb: return "Cache/Fonts/kingsbridge cd sb.otf";
            case Fonts::Kingsbridge_Cd_Ul_It: return "Cache/Fonts/kingsbridge cd ul it.otf";
            case Fonts::Kingsbridge_Cd_Ul: return "Cache/Fonts/kingsbridge cd ul.otf";
            case Fonts::Kingsbridge_El_It: return "Cache/Fonts/kingsbridge el it.otf";
            case Fonts::Kingsbridge_El: return "Cache/Fonts/kingsbridge el.otf";
            case Fonts::Kingsbridge_Ex_Bd_It: return "Cache/Fonts/kingsbridge ex bd it.otf";
            case Fonts::Kingsbridge_Ex_Bd: return "Cache/Fonts/kingsbridge ex bd.otf";
            case Fonts::Kingsbridge_Ex_Bk_It: return "Cache/Fonts/kingsbridge ex bk it.otf";
            case Fonts::Kingsbridge_Ex_Bk: return "Cache/Fonts/kingsbridge ex bk.otf";
            case Fonts::Kingsbridge_Ex_El_It: return "Cache/Fonts/kingsbridge ex el it.otf";
            case Fonts::Kingsbridge_Ex_El: return "Cache/Fonts/kingsbridge ex el.otf";
            case Fonts::Kingsbridge_Ex_Lt_It: return "Cache/Fonts/kingsbridge ex lt it.otf";
            case Fonts::Kingsbridge_Ex_Lt: return "Cache/Fonts/kingsbridge ex lt.otf";
            case Fonts::Kingsbridge_Ex_Rg_It: return "Cache/Fonts/kingsbridge ex rg it.otf";
            case Fonts::Kingsbridge_Ex_Rg: return "Cache/Fonts/kingsbridge ex rg.otf";
            case Fonts::Kingsbridge_Ex_Sb_It: return "Cache/Fonts/kingsbridge ex sb it.otf";
            case Fonts::Kingsbridge_Ex_Sb: return "Cache/Fonts/kingsbridge ex sb.otf";
            case Fonts::Kingsbridge_Ex_Ul_It: return "Cache/Fonts/kingsbridge ex ul it.otf";
            case Fonts::Kingsbridge_Ex_Ul: return "Cache/Fonts/kingsbridge ex ul.otf";
            case Fonts::Kingsbridge_Lt_It: return "Cache/Fonts/kingsbridge lt it.otf";
            case Fonts::Kingsbridge_Lt: return "Cache/Fonts/kingsbridge lt.otf";
            case Fonts::Kingsbridge_Rg_It: return "Cache/Fonts/kingsbridge rg it.otf";
            case Fonts::Kingsbridge_Rg: return "Cache/Fonts/kingsbridge rg.otf";
            case Fonts::Kingsbridge_Sb_It: return "Cache/Fonts/kingsbridge sb it.otf";
            case Fonts::Kingsbridge_Sb: return "Cache/Fonts/kingsbridge sb.otf";
            case Fonts::Kingsbridge_Sc_Bd_It: return "Cache/Fonts/kingsbridge sc bd it.otf";
            case Fonts::Kingsbridge_Sc_Bd: return "Cache/Fonts/kingsbridge sc bd.otf";
            case Fonts::Kingsbridge_Sc_Bk_It: return "Cache/Fonts/kingsbridge sc bk it.otf";
            case Fonts::Kingsbridge_Sc_Bk: return "Cache/Fonts/kingsbridge sc bk.otf";
            case Fonts::Kingsbridge_Sc_El_It: return "Cache/Fonts/kingsbridge sc el it.otf";
            case Fonts::Kingsbridge_Sc_El: return "Cache/Fonts/kingsbridge sc el.otf";
            case Fonts::Kingsbridge_Sc_Lt_It: return "Cache/Fonts/kingsbridge sc lt it.otf";
            case Fonts::Kingsbridge_Sc_Lt: return "Cache/Fonts/kingsbridge sc lt.otf";
            case Fonts::Kingsbridge_Sc_Rg_It: return "Cache/Fonts/kingsbridge sc rg it.otf";
            case Fonts::Kingsbridge_Sc_Rg: return "Cache/Fonts/kingsbridge sc rg.otf";
            case Fonts::Kingsbridge_Sc_Sb_It: return "Cache/Fonts/kingsbridge sc sb it.otf";
            case Fonts::Kingsbridge_Sc_Sb: return "Cache/Fonts/kingsbridge sc sb.otf";
            case Fonts::Kingsbridge_Sc_Ul_It: return "Cache/Fonts/kingsbridge sc ul it.otf";
            case Fonts::Kingsbridge_Sc_Ul: return "Cache/Fonts/kingsbridge sc ul.otf";
            case Fonts::Kingsbridge_Ul_It: return "Cache/Fonts/kingsbridge ul it.otf";
            case Fonts::Kingsbridge_Ul: return "Cache/Fonts/kingsbridge ul.otf";
            case Fonts::Kirsty_Bd_It: return "Cache/Fonts/Kirsty Bd It.otf";
            case Fonts::Kirsty_Bd: return "Cache/Fonts/Kirsty Bd.otf";
            case Fonts::Kirsty_Rg_It: return "Cache/Fonts/Kirsty Rg It.otf";
            case Fonts::Kirsty_Rg: return "Cache/Fonts/Kirsty Rg.otf";
            case Fonts::Kleptocracy_Titling_Bd: return "Cache/Fonts/kleptocracy titling bd.otf";
            case Fonts::Kleptocracy_Titling_Cd_Bd: return "Cache/Fonts/kleptocracy titling cd bd.otf";
            case Fonts::Kleptocracy_Titling_Cd_Lt: return "Cache/Fonts/kleptocracy titling cd lt.otf";
            case Fonts::Kleptocracy_Titling_Cd_Rg: return "Cache/Fonts/kleptocracy titling cd rg.otf";
            case Fonts::Kleptocracy_Titling_Ex_Bd: return "Cache/Fonts/kleptocracy titling ex bd.otf";
            case Fonts::Kleptocracy_Titling_Ex_Lt: return "Cache/Fonts/kleptocracy titling ex lt.otf";
            case Fonts::Kleptocracy_Titling_Ex_Rg: return "Cache/Fonts/kleptocracy titling ex rg.otf";
            case Fonts::Kleptocracy_Titling_Lt: return "Cache/Fonts/kleptocracy titling lt.otf";
            case Fonts::Kleptocracy_Titling_Rg: return "Cache/Fonts/kleptocracy titling rg.otf";
            case Fonts::Larabiefont_Rg: return "Cache/Fonts/Larabiefont Rg.otf";
            case Fonts::Libel_Suit_Suit_Rg: return "Cache/Fonts/Libel Suit Suit Rg.otf";
            case Fonts::Meloche_Lt: return "Cache/Fonts/Meloche Lt.otf";
            case Fonts::Mexcellent_3D: return "Cache/Fonts/Mexcellent 3d.otf";
            case Fonts::Mexcellent_Rg: return "Cache/Fonts/Mexcellent Rg.otf";
            case Fonts::Mixolydian_Titling_Bd_It: return "Cache/Fonts/Mixolydian Titling Bd It.otf";
            case Fonts::Mixolydian_Titling_Bd: return "Cache/Fonts/Mixolydian Titling Bd.otf";
            case Fonts::Mixolydian_Titling_El_It: return "Cache/Fonts/Mixolydian Titling El It.otf";
            case Fonts::Mixolydian_Titling_El: return "Cache/Fonts/Mixolydian Titling El.otf";
            case Fonts::Mixolydian_Titling_Hl_It: return "Cache/Fonts/Mixolydian Titling Hl It.otf";
            case Fonts::Mixolydian_Titling_Hl: return "Cache/Fonts/Mixolydian Titling Hl.otf";
            case Fonts::Mixolydian_Titling_Lt_It: return "Cache/Fonts/Mixolydian Titling Lt It.otf";
            case Fonts::Mixolydian_Titling_Lt: return "Cache/Fonts/Mixolydian Titling Lt.otf";
            case Fonts::Mixolydian_Titling_Rg_It: return "Cache/Fonts/Mixolydian Titling Rg It.otf";
            case Fonts::Mixolydian_Titling_Rg: return "Cache/Fonts/Mixolydian Titling Rg.otf";
            case Fonts::Mixolydian_Titling_Th_It: return "Cache/Fonts/Mixolydian Titling Th It.otf";
            case Fonts::Mixolydian_Titling_Th: return "Cache/Fonts/Mixolydian Titling Th.otf";
            case Fonts::Monofonto_Rg: return "Cache/Fonts/monofonto rg.otf";
            case Fonts::Mufferaw_Rg: return "Cache/Fonts/Mufferaw Rg.otf";
            case Fonts::Nasalization_Rg: return "Cache/Fonts/Nasalization Rg.otf";
            case Fonts::Negotiate_Rg: return "Cache/Fonts/Negotiate Rg.otf";
            case Fonts::Neuropol_X_Rg: return "Cache/Fonts/Neuropol X Rg.otf";
            case Fonts::Neuropolitical_Rg: return "Cache/Fonts/Neuropolitical Rg.otf";
            case Fonts::Nulshock_Bd: return "Cache/Fonts/Nulshock Bd.otf";
            case Fonts::Octin_College_Rg: return "Cache/Fonts/Octin College Rg.otf";
            case Fonts::Octin_Prison_Rg: return "Cache/Fonts/Octin Prison Rg.otf";
            case Fonts::Octin_Sports_Rg: return "Cache/Fonts/Octin Sports Rg.otf";
            case Fonts::Octin_Spraypaint_A_Rg: return "Cache/Fonts/Octin Spraypaint A Rg.otf";
            case Fonts::Octin_Stencil_Rg: return "Cache/Fonts/Octin Stencil Rg.otf";
            case Fonts::Octin_Vintage_B_Rg: return "Cache/Fonts/Octin Vintage B Rg.otf";
            case Fonts::Pakenham_Rg: return "Cache/Fonts/pakenham rg.otf";
            case Fonts::Palamecia_Titling: return "Cache/Fonts/Palamecia Titling.otf";
            case Fonts::Pirulen_Rg: return "Cache/Fonts/Pirulen Rg.otf";
            case Fonts::Pricedown_Bl: return "Cache/Fonts/Pricedown Bl.otf";
            case Fonts::Pupcat_Rg: return "Cache/Fonts/Pupcat Rg.otf";
            case Fonts::Quasix_Titling: return "Cache/Fonts/quasix titling.otf";
            case Fonts::Rakesly_Bd_It: return "Cache/Fonts/Rakesly Bd It.otf";
            case Fonts::Rakesly_Bd: return "Cache/Fonts/Rakesly Bd.otf";
            case Fonts::Rakesly_El_It: return "Cache/Fonts/Rakesly El It.otf";
            case Fonts::Rakesly_El: return "Cache/Fonts/Rakesly El.otf";
            case Fonts::Rakesly_Hl_It: return "Cache/Fonts/Rakesly Hl It.otf";
            case Fonts::Rakesly_Hl: return "Cache/Fonts/Rakesly Hl.otf";
            case Fonts::Rakesly_Lt_It: return "Cache/Fonts/Rakesly Lt It.otf";
            case Fonts::Rakesly_Lt: return "Cache/Fonts/Rakesly Lt.otf";
            case Fonts::Rakesly_Rg_It: return "Cache/Fonts/Rakesly Rg It.otf";
            case Fonts::Rakesly_Rg: return "Cache/Fonts/Rakesly Rg.otf";
            case Fonts::Rakesly_Th_It: return "Cache/Fonts/Rakesly Th It.otf";
            case Fonts::Rakesly_Th: return "Cache/Fonts/Rakesly Th.otf";
            case Fonts::Recharge_Bd: return "Cache/Fonts/Recharge Bd.otf";
            case Fonts::Remissis_Sb: return "Cache/Fonts/Remissis Sb.otf";
            case Fonts::Rexlia_Rg: return "Cache/Fonts/Rexlia Rg.otf";
            case Fonts::Rimouski_Sb: return "Cache/Fonts/rimouski sb.otf";
            case Fonts::Shlop_Rg: return "Cache/Fonts/shlop rg.otf";
            case Fonts::Sofachrome_Rg_It: return "Cache/Fonts/Sofachrome Rg It.otf";
            case Fonts::Sofachrome_Rg: return "Cache/Fonts/Sofachrome Rg.otf";
            case Fonts::Steelfish_Bd_It: return "Cache/Fonts/Steelfish Bd It.otf";
            case Fonts::Steelfish_Bd: return "Cache/Fonts/Steelfish Bd.otf";
            case Fonts::Steelfish_Eb_It: return "Cache/Fonts/Steelfish Eb It.otf";
            case Fonts::Steelfish_Eb: return "Cache/Fonts/Steelfish Eb.otf";
            case Fonts::Steelfish_Outline: return "Cache/Fonts/Steelfish Outline.otf";
            case Fonts::Steelfish_Rg_It: return "Cache/Fonts/Steelfish Rg It.otf";
            case Fonts::Steelfish_Rg: return "Cache/Fonts/Steelfish Rg.otf";
            case Fonts::Steelfish_Rounded_Bd: return "Cache/Fonts/Steelfish Rounded Bd.otf";
            case Fonts::Strenuous_3D: return "Cache/Fonts/Strenuous 3d.otf";
            case Fonts::Strenuous_Bl: return "Cache/Fonts/Strenuous Bl.otf";
            case Fonts::Sui_Generis_Rg: return "Cache/Fonts/Sui Generis Rg.otf";
            case Fonts::Toxigenesis_Bd: return "Cache/Fonts/toxigenesis bd.otf";
            case Fonts::Venus_Rising_Rg: return "Cache/Fonts/Venus Rising Rg.otf";
            case Fonts::Vinque_Rg: return "Cache/Fonts/Vinque Rg.otf";
            case Fonts::Vipnagorgialla_Bd_It: return "Cache/Fonts/Vipnagorgialla Bd It.otf";
            case Fonts::Vipnagorgialla_Bd: return "Cache/Fonts/Vipnagorgialla Bd.otf";
            case Fonts::Vipnagorgialla_Rg_It: return "Cache/Fonts/Vipnagorgialla Rg It.otf";
            case Fonts::Vipnagorgialla_Rg: return "Cache/Fonts/Vipnagorgialla Rg.otf";
            case Fonts::Wheaton_Capitals: return "Cache/Fonts/wheaton capitals.otf";
            case Fonts::Zekton_Rg: return "Cache/Fonts/Zekton Rg.otf";
            case Fonts::Zrnic_Rg: return "Cache/Fonts/zrnic rg.otf";
            default: return "Cache/Fonts/autoradiographic rg it.otf";
            }
        }

    };

}
