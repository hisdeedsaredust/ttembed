ttembed
=======

NOTE: Archived 22 December 2022. I have no further interest in this project.

Remove embedding limitations from TrueType fonts, by setting the fsType field
in the OS/2 table to zero. That's it; this program is a one-trick pony.

This is a version of "embed" by Tom Murphy VII. The original
is available at http://carnage-melon.tom7.org/embed/

This version differs in just a few ways:

* Checks that we are modifying a TTF or OTF. You'd have to work quite hard
to make the original corrupt a non font file but all the same, I'm daft
enough to just do "ttembed *" and expect it to work.

* Correctly recalculates the checksum of the OS/2 table. The original
did a bytewise sum, when it should be a 32-bit-word-wise-sum. Harder to
say the correct one than to do it.

* -n option to report when it would change a file, without doing it. It
will still be completely silent for files that don't need changing.

* Can change multiple fonts in one go.

This program exists because the default settings of some font creation 
programs are not "installable", even if that contradicts the licence you
are releasing the font under (particularly OFL, nowadays).
The only caveat with this program is the same one that Tom7 made quite clear
on his site: do not use this program to change the embedding settings
on fonts that you did not create or clearly allow you to modify them.

Example:

On my system, this command will list all the installed fonts that have limited embedding rights.


```
$ find /usr/share/fonts -iname '*.?tf' -print0 | xargs -0 ttembed -n
fstype=0008 /usr/share/fonts/google-droid/DroidSansJapanese.ttf
fstype=0008 /usr/share/fonts/google-droid/DroidSansTamil-Regular.ttf
fstype=0008 /usr/share/fonts/google-droid/DroidSansFallback.ttf
fstype=0008 /usr/share/fonts/google-droid/DroidSansHebrew-Bold.ttf
fstype=0008 /usr/share/fonts/google-droid/DroidSansEthiopic-Regular.ttf
fstype=0008 /usr/share/fonts/google-droid/DroidSansTamil-Bold.ttf
fstype=0008 /usr/share/fonts/google-droid/DroidSansHebrew-Regular.ttf
fstype=0008 /usr/share/fonts/google-droid/DroidSansThai.ttf
fstype=0008 /usr/share/fonts/google-droid/DroidSans.ttf
fstype=0008 /usr/share/fonts/google-droid/DroidSansDevanagari-Regular.ttf
fstype=0008 /usr/share/fonts/google-droid/DroidSansEthiopic-Bold.ttf
fstype=0008 /usr/share/fonts/google-droid/DroidSansGeorgian.ttf
fstype=0008 /usr/share/fonts/google-droid/DroidSansArabic.ttf
fstype=0008 /usr/share/fonts/google-droid/DroidSansArmenian.ttf
fstype=0008 /usr/share/fonts/google-droid/DroidSans-Bold.ttf
fstype=0008 /usr/share/fonts/thibault/StayPuft.ttf
fstype=0008 /usr/share/fonts/thibault/Rockets.ttf
fstype=0008 /usr/share/fonts/thibault/Isabella.ttf
fstype=0004 /usr/share/fonts/tlomt-junction/junction.otf
fstype=0008 /usr/share/fonts/hiran-perizia/Perizia.ttf
fstype=0008 /usr/share/fonts/opensymbol/opens___.ttf
fstype=0008 /usr/share/fonts/oflb-dignas-handwriting/phranzysko_-_Digna_s_Handwriting.ttf
fstype=0004 /usr/share/fonts/ns-tiza-chalk/tiza_chalk.ttf
fstype=0004 /usr/share/fonts/tlomt-sniglet/Sniglet.ttf
fstype=0008 /usr/share/fonts/oflb-sportrop/Sportrop.ttf
fstype=0004 /usr/share/fonts/tlomt-league-gothic/League Gothic.otf
fstype=0004 /usr/share/fonts/ns-bola/bola.ttf
```

As all of these fonts are shipped with licences that permit modification, I can then use ttembed to fix them.
