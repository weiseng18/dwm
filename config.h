/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 7;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 7;       /* vert inner gap between windows */
static const unsigned int gappoh    = 7;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 7;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "NotoSansDisplay Nerd Font:SemiBold:size=10" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#0092cc";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray2,  col_cyan  },
	[SchemeTitle] = { col_gray3, col_gray1, col_gray2 },
};

/* tagging */
// rename workspaces
static const char *tags[] = { "1", "2", "3", "4", "W", "E", "R" };

// rules fix window spawning location
// disabled
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	//{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	//{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ NULL,       NULL,       NULL,       0,            False,       -1 },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
 	/* symbol     arrange function */
 	{ "[]=",      tile },    /* first entry is default */
 	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
 };

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define Alt_M Mod1Mask // Alt Key
#define Ctrl_M ControlMask
#define Shft_M ShiftMask
#define Window_M Mod4Mask // Window Key
#define Hypr_M Window_M|Alt_M|Ctrl_M|Shft_M

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define XK_F1 0xffbe
#define XK_F2 0xffbf
#define XK_F3 0xffc0
#define XK_F4 0xffc1
#define XK_F5 0xffc2
#define XK_F6 0xffc3
#define XK_F7 0xffc4
#define XK_F8 0xffc5
#define XK_F9 0xffc6
#define XK_F10 0xffc7
#define XK_F11 0xffc8
#define XK_F12 0xffc9

#define BRIGHTNESS_UP SHCMD("~/.local/bin/brightness-up")
#define BRIGHTNESS_DOWN SHCMD("~/.local/bin/brightness-down")
#define LOCK SHCMD("~/.local/bin/lock")
#define NAUTILUS SHCMD("~/.local/bin/nautilus-run")
#define ROFI SHCMD("~/.local/bin/rofi-run")
#define SCREENSHOT SHCMD("~/.local/bin/screenshot")
#define SCREENSHOT_CLIPBOARD SHCMD("~/.local/bin/screenshot-clipboard")
#define VOLUME_UP SHCMD("~/.local/bin/volume-up")
#define VOLUME_DOWN SHCMD("~/.local/bin/volume-down")

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *termcmd[]  = { "kitty", NULL };

#include "movestack.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	/* LOOP through focused window */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	//{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	//{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	/* CHANGE window size */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	/* CHANGE window hierarchy */
	{ MODKEY|ShiftMask,             XK_j,      movestack,       {.i = +1} },
	{ MODKEY|ShiftMask,             XK_k,      movestack,       {.i = -1} },
	//{ MODKEY,                       XK_Return, zoom,           {0} },
	/* TOGGLE between previous workspace */
	{ MODKEY,                       XK_Tab,    view,           {0} },
	/* KILL window */
	{ MODKEY|ShiftMask,      XK_q,      killclient,     {0} },
	/* SET tiled layout */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	/* SET enable floating layout */
	//{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	/* SET maximized layout */
	//{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	/* TOGGLE maximized layout */
	{ MODKEY,                       XK_m,  setlayout,      {0} },
	//{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	/* VIEW all windows */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	/* ADD all tags to current window */
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	/* Multiple monitors */
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	/* scripts */
	{ Ctrl_M|MODKEY,      XK_l,			spawn,         LOCK       },
	{ MODKEY,             XK_space, spawn,         ROFI       },
	{ MODKEY,             XK_n,     spawn,         NAUTILUS   },
	{ 0,                  XK_Print, spawn,         SCREENSHOT },
	{ Ctrl_M|ShiftMask,   XK_Print, spawn,         SCREENSHOT_CLIPBOARD },
	{ Ctrl_M,             XK_F5,    spawn,         BRIGHTNESS_DOWN },
	{ Ctrl_M,             XK_F6,    spawn,         BRIGHTNESS_UP },
	{ 0,                  XK_F11,   spawn,         VOLUME_DOWN },
	{ 0,                  XK_F12,   spawn,         VOLUME_UP },
	/* CTRL + SHIFT + ALT + NUM */
	/* allows viewing of the same window on another workspace */
	/* toggle tag status */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_w,                      4)
	TAGKEYS(                        XK_e,                      5)
	TAGKEYS(                        XK_r,                      6)
	{ Hypr_M,             XK_q,      quit,           {0} },
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


