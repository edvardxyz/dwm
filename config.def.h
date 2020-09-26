/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack:pixelsize=12:antialias=true:autohint=true", "-wuncon-siji-medium-r-normal--10-100-75-75-c-80-iso10646-1" };
static const char dmenufont[]       = "Hack:pixelsize=12:antialias=true:autohint=true";
static const char normbgcolor[]       = "#1e1e1e";
static const char normbordercolor[]       = "#1e1e1e";
static const char normfgcolor[]       = "#51afef";
static const char selfgcolor[]       = "#51afef";
static const char selbordercolor[]        = "#2257a0";
static const char selbgcolor[]        = "#3f3f3f";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor, selbgcolor,  selbordercolor  },
};

/* swallow emacs */
static const char emacsclient[] = "emacsclient";
static const char emacsname[] = "emacs@";

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "nnn", NULL };
const char *spcmd3[] = {"st", "-n", "passmenu", "-g", "58x14", "-e", "passmenunew",  NULL };
const char *spcmd4[] = {"st", "-n", "screenshot", "-g", "40x10", "-e", "prtscname",  NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spfm",    spcmd2},
	{"passmenu",   spcmd3},
	{"screenshot",   spcmd4},
};

/* tagging */
static const char *tags[] = { " "," "," "," "," "," "," "," "," " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "st-256color",NULL,   NULL,          0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
	{ NULL,		"spterm",	NULL,		   SPTAG(0),   1,		  1,          1,        -1 },
	{ NULL,		"spfm",		NULL,		   SPTAG(1),   1,		  1,          1,        -1 },
	{ NULL,		"passmenu", NULL,	   	   SPTAG(2),   1,		  1,          1,        -1 },
	{ NULL,		"screenshot", NULL,	   	   SPTAG(3),   1,		  1,          1,        -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " ",      tile },    /* first entry is default */
	{ " ",      NULL },    /* no layout function means floating behavior */
	{ " ",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *brightnessupcmd[] = { "brightnessctl", "s", "5%+", NULL };
static const char *brightnessdowncmd[] = { "brightnessctl", "s", "5%-", NULL };
static const char *volupcmd[] = { "amixer", "sset", "Master", "2%+", NULL };
static const char *voldowncmd[] = { "amixer", "sset", "Master", "2%-", NULL };
static const char *kblayoutcmd[] = { "kblayout", NULL };
static const char *mpvclipcmd[] = { "mpvclip", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *importcmd[]  = { "printfull", NULL };
static const char *slockcmd[]  = { "slock", NULL };


#include <X11/XF86keysym.h>
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_y,      spawn,          {.v = mpvclipcmd } },
	{ MODKEY|ShiftMask,		        XK_l,	   spawn,          {.v = kblayoutcmd } },
	{ MODKEY|ShiftMask,		        XK_f,	   spawn,          {.v = importcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_g,      spawn,          {.v = slockcmd } },
	{ MODKEY,            			XK_s,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_n,	   togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,           	XK_p,	   togglescratch,  {.ui = 2 } },
	{ MODKEY|ShiftMask,           	XK_s,	   togglescratch,  {.ui = 3 } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { 0,                            XF86XK_MonBrightnessUp, spawn, {.v = brightnessupcmd } },
    { 0,                            XF86XK_MonBrightnessDown, spawn, {.v = brightnessdowncmd } },
    { 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
    { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

