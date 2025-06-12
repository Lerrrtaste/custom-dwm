/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = {
	"monospace:size=10",
	/* "FiraCode Nerd Font:size=10::antialias=true:autohint=true", */
};
/* static const char dmenufont[]       = "FiraCode Nerd Font:size=10:antialias=true:autohint=true"; */
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* autostart */
static const char *const autostart[] = {
	"xcape", "-e", "#66=Escape", NULL,
	"picom", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tagsalt[] = {
	"", // Web
	"", // Emacs / IDEs
	"", // Terminals / Background Tasks
	"", // Documentation / Notes
	"󰭹 "// Comms
	"󰣳", //homelab
	"", //media
	"", //misc
	"", //misc
	"" // Games
};
static const int momentaryalttags = 0; /* 1 means alttags will show only when key is held down*/

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	     instance    title    tags mask     isfloating   isterminal      noswallow     monitor */
	{ "st-256color",     NULL,       NULL,    0,            0,     	     1,              -1,            -1 },


	//1: - Web
	{ "librewolf",         NULL,       NULL,    1 << 0,       0,           0,             -1,            -1 },

	//2: - Emacs / Code
	{ "Emacs",  		 NULL,       NULL,    1 << 1,       0,           0,             -1,            -1 },

	// 3: Project Specific (GUI Editor, IDE, Engine, Logs)
	{ NULL,    NULL,    "Godot",               1 << 2,       0, 		     0,             0,            -1     },
	{ NULL,    NULL,    "Screeps",             1 << 2,       0, 		     0,             0,            -1     },
	{ NULL,    NULL,    "podman",              1 << 2,       0, 		     0,             0,            -1     },
	{ NULL,    NULL,    "podman",              1 << 2,       0, 		     0,             0,            -1     },

	// 4: Docs + Notes
	{ "Joplin",         NULL,       NULL,    1 << 0,       0,           0,             -1,            -1 },

	// 5:  Comms
	{ "librewolf",         NULL,       NULL,    1 << 0,       0,           0,             -1,            -1 },
	{ "Microsoft Teams - Preview",NULL,NULL,  1 << 4,       0,           0,             -1,            -1 },

	// 6 Fun / Music / Podcast


	// 9 Gaming / Long Background Tasks
	{ "steam",           NULL,       NULL,    1 << 8,       0,           0,             -1,            -1 },

	// Notes / Docs
	{ NULL,             NULL,       "Joplin",  1 << 3,      0, 		    0,             -1,            -1     },
	{ NULL,             NULL,       "Signal",  1 << 4,      0, 		    0,             -1,            -1     }
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "HHH",      grid },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
};

/* key definitions */
#define MODKEY Mod1Mask
#define SUPERKEY Mod4Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN,    KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           CHAIN,    KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN,    KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, CHAIN,    KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* COMMANDS */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */


// spawn st
static const char *termcmd[]  = { "st", NULL };

// macos mode
static const char *macosquickstart[]  = { "quickemu", "--vm", "/media/data1/vms/macos-ventura.conf", "--fullscreen", "--display", "spice", NULL };
static const char *macoskill[]  = { "quickemu", "--vm", "/media/data1/vms/macos-ventura.conf", "--kill", NULL };
static const char *macoskillalt[]  = { "pkill", "macos", NULL };

// dmenu for all programs
static const char *dmenuallcmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };

// productivity browser (wavebox)
static const char *prodbrowsercmd[]  = { "librewolf", "--new-window", NULL };

// firefox distro
static const char *firefoxcmd[]  = { "librewolf", "--new-window", NULL };

static const char *emacsclientcmd[]  = { "emacsclient", "--create-frame", "-a" "emacs", NULL };
static const char *keepasscmd[]  = { "keepassxc", NULL };
static const char *slockcmd[]  = { "slock", NULL };
static const char *autorandrcmd[]  = { "autorandr", "horizontal", NULL };
static const char *maimrect[]  = { "maim", "-s", "-u", "-f png", "-q", "-o /home/lerrrtaste/screenshots/screenshot_$(date +'%Y-%m-%dT%H-%M-%S').png", NULL };
static const char *maimfull[]  = { "maim", "-u", "-f png", "-q", "-o /home/lerrrtaste/screenshots/screenshot_$(date +'%Y-%m-%dT%H-%M-%S').png", NULL };
static const char *screensaver[]  = { "xscreensaver", NULL };
static const char *dmenuprograms[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
/* static const char *lfcdcmd[]  = { "st", "-e", "lfcd", NULL }; // TODO make this work */


#include "movestack.c"
static Key keys[] = {
	/* modifier                     chain key   key        function        argument */


/* Experimental */

	/* { MODKEY|ShiftMask,             XK_c,         XK_k,      quitprompt,          {.v = macoskillalt } }, // macos kill alt */
	/*TODO read (from gpt) { MODKEY|ShiftMask,             XK_c,         XK_s,      spawn,          {.v = screensaver } }, // xscreensaver */
	/* { MODKEY|ShiftMask,             XK_c,         XK_0,      quitprompt,           {0} }, */





    /*
	 * BASICS
	 *
	 * SUPERKEY + Space:
	 * spawn terminal (st, termcmd func)
	 *
	 * */
	{ SUPERKEY,         -1,         XK_Return,         spawn,          {.v = termcmd } },

	/*
	 * DMENU
	 *
	 * SUPERKEY + P:
	 * spawn dmenu all (dmenucmd func)
	 *
	 * */
	/* { SUPERKEY,                       XK_space,       XK_space,  spawn,          {.v = dmenuallcmd } }, */
	{ SUPERKEY,                         -1,             XK_p,      spawn,          {.v = dmenuallcmd } },


	/* misc */
	{ MODKEY,                       -1,         XK_b,       togglebar,      {0} }, // toggle bar
	{ MODKEY,                       -1,         XK_Return, 	zoom,           {0} }, // zoom FIXME
	{ MODKEY,                       -1,         XK_Tab,     view,           {0} }, // toggle last tag

	/* // DMenu and st: */
	/* { SUPERKEY, 					-1,         XK_Return, spawn,          {.v = termcmd } }, */
	/* { SUPERKEY,               XK_space,         XK_space,  spawn,          {.v = dmenucmd } }, */


	/* tools */

	// Screenshot rect: MOD-s m -> rectangle select to /home/lerrrtaste/screenshots
	{ MODKEY,  						XK_s,       XK_m,      spawn,          {.v = maimrect} },
	// Screenshot full: MOD-s M -> fullscreen screen
	{ MODKEY, 						XK_s,       XK_M,      spawn,          {.v = maimfull} },

	// Mod s - l: screensaver
	{ MODKEY,                       XK_s,         XK_l,      spawn,          {.v = slockcmd} },
	// Mod s - x: apply auto auotrandr profile
	{ MODKEY,                       XK_s,         XK_x,      spawn,          SHCMD("autorandr --change") }, // trigger autorandr



	/* General Software */

	// EMACS: super e
	{ SUPERKEY,                       -1,       XK_e,      spawn,          {.v = emacsclientcmd } },

	// LibreWolf: super f
	{ SUPERKEY,                       -1,       XK_f,      spawn,          {.v = firefoxcmd } },

	// Protonmail: super s - m
	{ SUPERKEY,                       XK_s,     XK_p,      spawn,          SHCMD("proton-mail") },

	// ProtonVPN: super s - v
	{ SUPERKEY,                       XK_s,    XK_v,      spawn,          SHCMD("proton-vpn-gui") },

	// IVPN: super s - i
	{ SUPERKEY,                       XK_s,       XK_i,      spawn,          SHCMD("ivpn") },

	// macos
	{ MODKEY|ShiftMask,             XK_c,         XK_m,      spawn,          {.v = macoskill } }, // macos kill
	{ MODKEY|ShiftMask,             XK_s,         XK_m,      spawn,          {.v = macosquickstart } }, // macos quickstart

	/* Password Manager */
	//  Super k - k: keepassxc
	{ SUPERKEY,                       XK_k,    XK_k,      spawn,          {.v = keepasscmd } },

	// super k - p: proton-pass
	{ SUPERKEY,                       XK_k,    XK_p,      spawn,          SHCMD("proton-pass") },

	// Super s - b: bitwarden
	{ SUPERKEY,                       XK_k,    XK_m,      spawn,          SHCMD("bitwarden") },

	// Super s - b: bitwarden
	{ SUPERKEY,                       XK_k,    XK_y,      spawn,          SHCMD("yubioath-flutter") },


	/* scratchpads (Mod-a)*/
    { MODKEY,                       -1,         XK_w,      scratchpad_show, {.i = 1} },
    { MODKEY,                       -1,         XK_y,      scratchpad_show, {.i = 2} },
    /* { MODKEY,                       XK_a,         XK_o,      scratchpad_show, {.i = 3} }, */
    { MODKEY|ShiftMask,             -1,         XK_w,      scratchpad_hide, {.i = 1} }, // create scratchpad
    { MODKEY|ShiftMask,             -1,         XK_y,      scratchpad_hide, {.i = 2} },
    /* { MODKEY|ShiftMask,             XK_a,         XK_o,      scratchpad_hide, {.i = 3} }, */
	{ MODKEY|ShiftMask,             -1,         XK_r,      scratchpad_remove,           {0} },

	/* switch layouts */
	{ MODKEY,                       -1,         XK_t,      setlayout,      {.v = &layouts[0]} }, // tile
	{ MODKEY,                       -1,         XK_g,      setlayout,      {.v = &layouts[1]} }, // grid
	{ MODKEY,                       -1,         XK_f,      setlayout,      {.v = &layouts[2]} }, // floating
	{ MODKEY,                       -1,         XK_m,      setlayout,      {.v = &layouts[3]} }, // monocel
	{ MODKEY,                       -1,         XK_u,      setlayout,      {.v = &layouts[4]} }, // centered master
	{ MODKEY,                       -1,         XK_o,      setlayout,      {.v = &layouts[5]} }, // centered floating master
	{ MODKEY|ShiftMask,             -1,         XK_t,      setlayout,      {.v = &layouts[6]} }, // bottom stack
	{ MODKEY|ShiftMask,             -1,         XK_b,      setlayout,      {.v = &layouts[7]} }, // bottom stack horizontal
	{ MODKEY,                       -1,         XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             -1,         XK_space,  togglefloating, {0} },

	/* layout options */
	{ MODKEY,                       -1,         XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       -1,         XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       -1,         XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       -1,         XK_l,      setmfact,       {.f = +0.05} },
 	{ MODKEY|ShiftMask,             -1,         XK_h,      setcfact,       {.f = +0.25} },
 	{ MODKEY|ShiftMask,             -1,         XK_l,      setcfact,       {.f = -0.25} },
 	{ MODKEY|ShiftMask,             -1,         XK_o,      setcfact,       {.f =  0.00} },

	/* clients */
	{ MODKEY|ShiftMask,             -1,         XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             -1,         XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       -1,         XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       -1,         XK_k,      focusstack,     {.i = -1 } },

	/* monitors */
	{ MODKEY|ShiftMask,             -1,         XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             -1,         XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       -1,         XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       -1,         XK_period, focusmon,       {.i = +1 } },

	/* tags */
	{ MODKEY,                       -1,         XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             -1,         XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       -1,         XK_n,      togglealttag,   {0} },
	TAGKEYS(                        -1,         XK_1,                      0)
	TAGKEYS(                        -1,         XK_2,                      1)
	TAGKEYS(                        -1,         XK_3,                      2)
	TAGKEYS(                        -1,         XK_4,                      3)
	TAGKEYS(                        -1,         XK_5,                      4)
	TAGKEYS(                        -1,         XK_6,                      5)
	TAGKEYS(                        -1,         XK_7,                      6)
	TAGKEYS(                        -1,         XK_8,                      7)
	TAGKEYS(                        -1,         XK_9,                      8)

	/* quitting things (Mod-c) */
	{ MODKEY|ShiftMask,             XK_c,         XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_c,         XK_q,      quitprompt,           {0} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

