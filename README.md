# My build of DWM - from [*suckless.org*](https://www.suckless.org)
## I dont use this anymore- i use savedconfig useflag in gentoo and patch through portage

I changed to using emerge to compile dwm from gentoo repo with savedconfig. 
dwm config in /etc/portage/savedconfig/x11-wm and patches go in /etc/portage/patches/x11-wm/dwm

__________________________________________________________

Every patch and custom code changes are in seperate branches.
I use a script to merge them all together and compile (see [script](https://github.com/edvardxyz/dotfiles/blob/master/.local/bin/suckmerge)).
