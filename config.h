/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
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
static const char *tagsalt[] = { "3", "4", "5", "5", "6", "7", "8", "9", "10" };
static const int momentaryalttags = 0; /* 1 means alttags will show only when key is held down*/

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	     instance    title    tags mask     isfloating   isterminal      noswallow     monitor */
	{ "st",              NULL,       NULL,    0,            0,     	     1,              0,            -1 },
	{ "Gimp",            NULL,       NULL,    0,            1,           0,              0,            -1 },
	{ "Firefox",         NULL,       NULL,    1 << 8,       0,           0,             -1,            -1 },
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

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *firefoxcmd[]  = { "firefox", "--new-window", NULL };
static const char *emacsclientcmd[]  = { "emacsclient", "--create-frame", "-a" "emacs", NULL };
static const char *keepasscmd[]  = { "keepassxc", NULL };
static const char *slockcmd[]  = { "slock", NULL };
static const char *autorandrcmd[]  = { "autorandr", "horizontal", NULL };


#include "movestack.c"
static Key keys[] = {
	/* modifier                     chain key   key        function        argument */
	/* general */
	{ MODKEY|ShiftMask,             -1,         XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       -1,         XK_b,      togglebar,      {0} },
	{ MODKEY,                       -1,         XK_Return, zoom,           {0} },
	{ MODKEY,                       -1,         XK_Tab,    view,           {0} },

	/* programs (Mod-s)*/
	{ SUPERKEY,                       XK_space,       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                         -1,             XK_p,      spawn,          {.v = dmenucmd } },
	{ SUPERKEY,                       XK_space,       XK_t,      spawn,          {.v = termcmd } },
	{ SUPERKEY,                       XK_space,       XK_f,      spawn,          {.v = firefoxcmd } },
	{ SUPERKEY,                       XK_space,       XK_e,      spawn,          {.v = emacsclientcmd } },
	{ SUPERKEY,                       XK_space,       XK_k,      spawn,          {.v = keepasscmd } },

	/* shortcuts */
	{ MODKEY,                       XK_s,       XK_m,      spawn,          SHCMD("maim -s -u -f png -q -o /home/lerrrtaste/screenshots/screenshot_$(date +'%Y-%m-%dT%H-%M-%S').png") },
	{ MODKEY,                       XK_s,         XK_r,      spawn,          {.v = autorandrcmd} },
	{ MODKEY,                       XK_s,         XK_l,      spawn,          {.v = slockcmd} },


	/* scratchpads (Mod-a)*/
    { MODKEY,                       XK_a,         XK_j,      scratchpad_show, {.i = 1} },
    { MODKEY,                       XK_a,         XK_k,      scratchpad_show, {.i = 2} },
    { MODKEY,                       XK_a,         XK_l,      scratchpad_show, {.i = 3} },
    { MODKEY|ShiftMask,             XK_a,         XK_j,      scratchpad_hide, {.i = 1} }, // create scratchpad
    { MODKEY|ShiftMask,             XK_a,         XK_k,      scratchpad_hide, {.i = 2} },
    { MODKEY|ShiftMask,             XK_a,         XK_l,      scratchpad_hide, {.i = 3} },
	{ MODKEY|ShiftMask,             XK_a,         XK_r,      scratchpad_remove,           {0} },

	/* switch layouts */
	{ MODKEY,                       -1,         XK_t,      setlayout,      {.v = &layouts[0]} }, // tile
	{ MODKEY,                       -1,         XK_g,      setlayout,      {.v = &layouts[1]} }, // grid
	{ MODKEY,                       -1,         XK_f,      setlayout,      {.v = &layouts[2]} }, // floating
	{ MODKEY,                       -1,         XK_m,      setlayout,      {.v = &layouts[3]} }, // monocel
	{ MODKEY,                       -1,         XK_u,      setlayout,      {.v = &layouts[4]} }, // centered master
	{ MODKEY,                       -1,         XK_o,      setlayout,      {.v = &layouts[5]} }, // centered floating master
	/* { MODKEY|ShiftMask,             -1,         XK_t,      setlayout,      {.v = &layouts[6]} }, // bottom stack */
	{ MODKEY|ShiftMask,             -1,         XK_t,      setlayout,      {.v = &layouts[7]} }, // bottom stack horizontal
	{ MODKEY,                       -1,         XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             -1,         XK_space,  togglefloating, {0} },

	/* layout options */
	{ MODKEY,                       -1,         XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       -1,         XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       -1,         XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       -1,         XK_l,      setmfact,       {.f = +0.05} },

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

