/*
 * smash.cpp
 *
 *  Created on: May 24, 2016
 *      Author: sumanth
 */

#include <string>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <algorithm>

using namespace std;
const char *list[] = { "bash", "bunzip2", "busybox", "bzcat", "bzcmp", "bzdiff",
		"bzegrep", "bzexe", "bzfgrep", "bzgrep", "bzip2", "bzip2recover",
		"bzless", "bzmore", "cat", "chacl", "chgrp", "chmod", "chown", "chvt",
		"cp", "cpio", "dash", "date", "dbus-cleanup-sockets", "dbus-daemon",
		"dbus-uuidgen", "dd", "df", "dir", "dmesg", "dnsdomainname",
		"domainname", "dumpkeys", "echo", "ed", "efibootmgr", "egrep", "false",
		"fgconsole", "fgrep", "findmnt", "fuser", "fusermount", "getfacl",
		"grep", "gunzip", "gzexe", "gzip", "hostname", "ip", "kbd_mode", "kill",
		"kmod", "less", "lessecho", "lessfile", "lesskey", "lesspipe", "ln",
		"loadkeys", "login", "loginctl", "lowntfs-3g", "ls", "lsblk", "lsmod",
		"mkdir", "mknod", "mktemp", "more", "mount", "mountpoint", "mt",
		"mt-gnu", "mv", "nano", "nc", "nc.openbsd", "netcat", "netstat",
		"nisdomainname", "ntfs-3g", "ntfs-3g.probe", "ntfs-3g.secaudit",
		"ntfs-3g.usermap", "ntfscat", "ntfsck", "ntfscluster", "ntfscmp",
		"ntfsdump_logfile", "ntfsfix", "ntfsinfo", "ntfsls", "ntfsmftalloc",
		"ntfsmove", "ntfstruncate", "ntfswipe", "open", "openvt", "pidof",
		"ping", "ping6", "plymouth", "plymouth-upstart-bridge", "ps", "pwd",
		"rbash", "readlink", "red", "rm", "rmdir", "rnano",
		"running-in-container", "run-parts", "sed", "setfacl", "setfont",
		"setupcon", "sh", "sh.distrib", "sleep", "ss", "static-sh", "stty",
		"su", "sync", "tailf", "tar", "tempfile", "touch", "true", "udevadm",
		"ulockmgr_server", "umount", "uname", "uncompress", "unicode_start",
		"vdir", "vmmouse_detect", "which", "whiptail", "ypdomainname", "zcat",
		"zcmp", "zdiff", "zegrep", "zfgrep", "zforce", "zgrep", "zless",
		"zmore", "znew", "make", "history", "clear", "gedit", "[", "2to3",
		"2to3-2.7", "2to3-3.4", "411toppm", "7z", "7za", "a2p", "accountwizard",
		"aclocal", "aclocal-1.14", "aconnect", "acpi_listen",
		"activity-log-manager", "add-apt-repository", "addpart", "addr2line",
		"akonadi_agent_launcher", "akonadi_agent_server",
		"akonadi_archivemail_agent", "akonadi_baloo_indexer",
		"akonadi_birthdays_resource", "akonadi_control", "akonadictl",
		"akonadi_davgroupware_resource", "akonadi_facebook_resource",
		"akonadi_googlecalendar_resource", "akonadi_googlecontacts_resource",
		"akonadi_icaldir_resource", "akonadi_imap_resource",
		"akonadi_invitations_agent", "akonadi_kabc_resource",
		"akonadi_kcal_resource", "akonadi_kdeaccounts_resource",
		"akonadi_kolabproxy_resource", "akonadi_localbookmarks_resource",
		"akonadi_maildispatcher_agent", "akonadi_mailfilter_agent",
		"akonadi_mailtransport_dummy_resource", "akonadi_migration_agent",
		"akonadi_mixedmaildir_resource", "akonadi_newmailnotifier_agent",
		"akonadi_nntp_resource", "akonadi_notes_agent",
		"akonadi_openxchange_resource", "akonadi_pop3_resource", "akonadi_rds",
		"akonadi_sendlater_agent", "akonadiserver", "akonaditray",
		"akonadi_vcarddir_resource", "akregator", "akregatorstorageexporter",
		"alsaloop", "alsamixer", "alsaucm", "amarok", "amarok_afttagger",
		"amarokcollectionscanner", "amarokmp3tunesharmonydaemon", "amarokpkg",
		"amidi", "amixer", "amuFormat.sh", "amzdownloader", "animate",
		"animate.im6", "anytopnm", "apg", "apgbfm", "aplay", "aplaymidi",
		"appletviewer", "apport-bug", "apport-cli", "apport-collect",
		"apport-unpack", "appres", "apropos", "apt", "apt-add-repository",
		"apt-cache", "apt-cdrom", "apt-config", "aptdcon",
		"apt-extracttemplates", "apt-ftparchive", "apt-get", "apt-key",
		"apt-mark", "apt-sortpkgs", "apturl", "apturl-gtk", "apturl-kde", "ar",
		"arch", "arecord", "arecordmidi", "ark", "arm2hpdl", "arping", "as",
		"asapcat", "asciitopgm", "aseqdump", "aseqnet", "aspell",
		"aspell-import", "assistant", "atktopbm", "atobm", "attr", "autoconf",
		"autoheader", "autom4te", "automake", "automake-1.14", "autoreconf",
		"autoscan", "autoupdate", "avahi-browse", "avahi-browse-domains",
		"avahi-publish", "avahi-publish-address", "avahi-publish-service",
		"avahi-resolve", "avahi-resolve-address", "avahi-resolve-host-name",
		"avahi-set-host-name", "awk", "axi-cache", "balooctl", "baloo_file",
		"baloo_file_cleaner", "baloo_file_extractor", "baloosearch",
		"balooshow", "baobab", "base64", "basename", "bashbug", "bc",
		"bcompare", "bcp", "bdftopcf", "bdftruncate", "bioradtopgm", "bison",
		"bison.yacc", "bitmap", "bjam", "bluedevil-audio", "bluedevil-helper",
		"bluedevil-input", "bluedevil-monolithic", "bluedevil-network-dun",
		"bluedevil-network-panu", "bluedevil-sendfile", "bluedevil-wizard",
		"bluetooth-agent", "bluetooth-sendto", "bluetooth-wizard",
		"bluez-simple-agent", "bluez-simple-service", "bluez-test-adapter",
		"bluez-test-audio", "bluez-test-device", "bluez-test-discovery",
		"bluez-test-input", "bluez-test-manager", "bluez-test-network",
		"bluez-test-serial", "bluez-test-service", "bluez-test-telephony",
		"bmptopnm", "bmptoppm", "bmtoa", "brasero", "brltty-ctb",
		"brltty-trtxt", "brltty-ttb", "brushtopbm", "bsd-from", "bsd-write",
		"btcflash", "c++", "c2ph", "c89", "c89-gcc", "c99", "c99-gcc", "cal",
		"calendar", "calendarjanitor", "calibrate_ppa", "callgrind_annotate",
		"callgrind_control", "canberra-gtk-play", "cancel",
		"canonical-certification-server", "canonical-driver-test-suite-cli",
		"captoinfo", "catchsegv", "catman", "cautious-launcher", "cc",
		"cd-create-profile", "cd-fix-profile", "cd-iccdump", "cdparanoia",
		"cdrdao", "cdrecord", "cdxa2mpeg", "c++filt", "cg_annotate", "cg_diff",
		"cg_merge", "chacl", "chage", "chardet", "chardet3", "chardetect3",
		"charmap", "chattr", "chcon", "checkbox", "checkbox-cli",
		"checkbox-gui", "check-language-support", "checksctp", "cheese", "chfn",
		"chkdupexe", "chrt", "chsh", "cifsdd", "ciptool", "ckbcomp",
		"ck-history", "ck-launch-session", "ck-list-sessions", "cksum", "clear",
		"clear_console", "cmake", "cmake-gui", "cmp", "cmuwmtopbm", "codepage",
		"col", "colcrt", "colord-kde-icc-importer", "colormgr", "colrm",
		"column", "combinediff", "comm", "compare", "compare.im6", "compiz",
		"compiz-decorator", "compose", "composite", "composite.im6",
		"config_data", "conjure", "conjure.im6", "convert", "convert.im6",
		"corelist", "cpack", "cpan", "cpan2dist", "cpanp", "cpanp-run-perl",
		"cpp", "cpp-4.8", "crc32", "credentials-preferences", "c_rehash",
		"crontab", "csplit", "ctest", "ctstat", "cups-calibrate", "cupstestdsc",
		"cupstestppd", "curl", "cut", "cvlc", "cvt", "dbus-launch",
		"dbus-monitor", "dbus-send", "dbwrap_tool", "dc", "dconf", "ddate",
		"deallocvt", "debconf", "debconf-apt-progress", "debconf-communicate",
		"debconf-copydb", "debconf-escape", "debconf-gettextize",
		"debconf-set-selections", "debconf-show", "debconf-updatepo",
		"deb-systemd-helper", "deb-systemd-invoke", "dehtmldiff", "deja-dup",
		"deja-dup-preferences", "delpart", "derb", "designer",
		"desktop-file-edit", "desktop-file-install", "desktop-file-validate",
		"devdump", "dfutool", "dgawk", "dh", "dh_apparmor", "dh_auto_build",
		"dh_auto_clean", "dh_auto_configure", "dh_auto_install", "dh_auto_test",
		"dh_autotools-dev_restoreconfig", "dh_autotools-dev_updateconfig",
		"dh_bash-completion", "dh_bugfiles", "dh_builddeb", "dh_clean",
		"dh_compress", "dh_desktop", "dh_dkms", "dh_fixperms", "dh_gconf",
		"dh_gencontrol", "dh_gtkmodules", "dh_icons", "dh_install",
		"dh_installcatalogs", "dh_installchangelogs", "dh_installcron",
		"dh_installdeb", "dh_installdebconf", "dh_installdirs",
		"dh_installdocs", "dh_installemacsen", "dh_installexamples",
		"dh_installgsettings", "dh_installifupdown", "dh_installinfo",
		"dh_installinit", "dh_installlogcheck", "dh_installlogrotate",
		"dh_installman", "dh_installmanpages", "dh_installmenu",
		"dh_installmime", "dh_installmodules", "dh_installpam", "dh_installppp",
		"dh_installudev", "dh_installwm", "dh_installxfonts",
		"dh_installxmlcatalogs", "dh_link", "dh_lintian", "dh_listpackages",
		"dh_makeshlibs", "dh_md5sums", "dh_movefiles", "dh_numpy",
		"dh_pangomodules", "dh_perl", "dh_prep", "dh_pypy", "dh_python2",
		"dh_python3", "dh_scrollkeeper", "dh_shlibdeps", "dh_strip",
		"dh_suidregister", "dh_testdir", "dh_testroot", "dh_ucf",
		"dh_undocumented", "dh_usrlocal", "dialog", "diff", "diff3", "diffstat",
		"dig", "dircolors", "dirname", "dirsplit", "display", "display.im6",
		"dm-tool", "dolphin", "do-release-upgrade", "dotlockfile", "dpkg",
		"dpkg-architecture", "dpkg-buildflags", "dpkg-buildpackage",
		"dpkg-checkbuilddeps", "dpkg-deb", "dpkg-distaddfile", "dpkg-divert",
		"dpkg-genchanges", "dpkg-gencontrol", "dpkg-gensymbols",
		"dpkg-log-summary", "dpkg-maintscript-helper", "dpkg-mergechangelogs",
		"dpkg-name", "dpkg-parsechangelog", "dpkg-query", "dpkg-scanpackages",
		"dpkg-scansources", "dpkg-shlibdeps", "dpkg-source", "dpkg-split",
		"dpkg-statoverride", "dpkg-trigger", "dpkg-vendor", "dragon", "du",
		"dumpiso", "dumpkeys", "duplicity", "dvd-ram-control",
		"dvd+rw-booktype", "dvd+rw-format", "dvd+rw-mediainfo", "dvipdf", "dwp",
		"easy_install", "easy_install-2.7", "edit", "editdiff", "editor",
		"editres", "eject", "elfedit", "empathy", "empathy-accounts",
		"empathy-debugger", "enc2xs", "enchant", "enchant-lsmod", "env",
		"envsubst", "eog", "eps2eps", "eqn", "erb", "erb1.9.1", "esc-m",
		"eventlogadm", "evince", "evince-previewer", "evince-thumbnailer", "ex",
		"expand", "expiry", "expr", "extcheck", "extresso", "eyuvtoppm", "f2py",
		"f2py2.7", "factor", "faillog", "faked-sysv", "faked-tcp", "fakeroot",
		"fakeroot-sysv", "fakeroot-tcp", "fallocate", "fc-cache", "fc-cat",
		"fc-list", "fc-match", "fc-pattern", "fc-query", "fc-scan",
		"fc-validate", "fiascotopnm", "filan", "file", "file-roller",
		"filezilla", "filterdiff", "find", "find2perl", "firefox", "fitstopnm",
		"fixcvsdiff", "fix-qdf", "flex", "flex++", "flipdiff", "flock", "fmt",
		"fold", "font2c", "fonttosfnt", "foo2hbpl2", "foo2hbpl2-wrapper",
		"foo2hiperc", "foo2hiperc-wrapper", "foo2hp", "foo2hp2600-wrapper",
		"foo2lava", "foo2lava-wrapper", "foo2oak", "foo2oak-wrapper",
		"foo2qpdl", "foo2qpdl-wrapper", "foo2slx", "foo2slx-wrapper", "foo2xqx",
		"foo2xqx-wrapper", "foo2zjs", "foo2zjs-icc2ps", "foo2zjs-pstops",
		"foo2zjs-wrapper", "free", "freetype-config", "friends-dispatcher",
		"friends-service", "from", "fslsfonts", "fstobdf", "fstopgm", "ftp",
		"funzip", "fzputtygen", "fzsftp", "g++", "g3topbm", "g++-4.8",
		"gamma4scanimage", "gatttool", "gawk", "gcalccmd", "gcc", "gcc-4.8",
		"gcc-ar", "gcc-ar-4.8", "gcc-nm", "gcc-nm-4.8", "gcc-ranlib",
		"gcc-ranlib-4.8", "gconf-merge-tree", "gconftool", "gconftool-2",
		"gcore", "gcov", "gcov-4.8", "gcr-viewer", "gdb", "gdbtui", "gdbus",
		"gdbus-codegen", "gdebi", "gdebi-gtk", "gdialog", "gdk-pixbuf-csource",
		"gdk-pixbuf-pixdata", "gdk-pixbuf-query-loaders", "gdmflexiserver",
		"gdm-screenshot", "gedit", "gem", "gem1.9.1", "gemtopbm", "gemtopnm",
		"genbrk", "gencat", "gencfu", "gencnval", "gendict", "genisoimage",
		"genrb", "genresscript", "geqn", "GET", "getconf", "geteltorito",
		"getent", "getfacl", "getfattr", "gethostip", "getkeycodes", "getopt",
		"gettext", "gettextize", "gettext.sh", "ghostscript", "gidmigrator",
		"giftopnm", "ginstall-info", "gio-querymodules", "gipddecode", "git",
		"git-receive-pack", "git-shell", "gitso", "git-upload-archive",
		"git-upload-pack", "gjs", "gjs-console", "gkbd-keyboard-display",
		"gksu", "gksudo", "gksu-properties", "glib-compile-resources",
		"glib-compile-schemas", "glib-genmarshal", "glib-gettextize",
		"glib-mkenums", "gmail-notify", "gnome-calculator",
		"gnome-character-map", "gnome-contacts", "gnome-control-center",
		"gnome-control-center.real", "gnome-disk-image-mounter", "gnome-disks",
		"gnome-file-share-properties", "gnome-font-viewer", "gnome-help",
		"gnome-keyring", "gnome-keyring-3", "gnome-keyring-daemon",
		"gnome-language-selector", "gnome-open", "gnome-power-statistics",
		"gnome-screensaver", "gnome-screensaver-command", "gnome-screenshot",
		"gnome-session", "gnome-session-inhibit", "gnome-session-properties",
		"gnome-session-quit", "gnome-settings-daemon", "gnome-shell",
		"gnome-shell-extension-prefs", "gnome-shell-extension-tool",
		"gnome-shell-perf-tool", "gnome-sound-applet", "gnome-system-log",
		"gnome-system-log-pkexec", "gnome-system-monitor", "gnome-terminal",
		"gnome-terminal.wrapper", "gnome-text-editor", "gnome-thumbnail-font",
		"gnome-www-browser", "gobject-query", "gold", "google-chrome",
		"google-chrome-stable", "gouldtoppm", "gparted-pkexec", "gpasswd",
		"gperf", "gpg", "gpg2", "gpg-agent", "gpgconf", "gpg-connect-agent",
		"gpgkey2ssh", "gpgsm", "gpgsm-gencert.sh", "gpgsplit", "gpgv",
		"gpg-zip", "gpic", "gprof", "gpu-manager", "grepdiff", "gresource",
		"groff", "grog", "grops", "grotty", "groups", "growisofs",
		"grub-editenv", "grub-file", "grub-fstest", "grub-glue-efi",
		"grub-kbdcomp", "grub-menulst2cfg", "grub-mkfont", "grub-mkimage",
		"grub-mklayout", "grub-mknetdir", "grub-mkpasswd-pbkdf2",
		"grub-mkrelpath", "grub-mkrescue", "grub-mkstandalone", "grub-mount",
		"grub-render-label", "grub-script-check", "grub-syslinux2cfg", "gs",
		"gsbj", "gsdj", "gsdj500", "gsettings", "gsettings-data-convert",
		"gsettings-schema-convert", "gslj", "gslp", "gsnd",
		"gst-discoverer-0.10", "gst-discoverer-1.0", "gst-feedback-0.10",
		"gst-inspect-0.10", "gst-inspect-1.0", "gst-install", "gst-launch-0.10",
		"gst-launch-1.0", "gst-play-1.0", "gstreamer-codec-install",
		"gst-typefind-0.10", "gst-typefind-1.0", "gst-visualise-0.10",
		"gst-xmlinspect-0.10", "gst-xmllaunch-0.10", "gtbl", "gtester",
		"gtester-report", "gtf", "gtk-builder-convert", "gtk-launch",
		"gtk-update-icon-cache", "gtk-update-icon-cache-3.0", "gtkvncviewer",
		"gtk-window-decorator", "gucharmap", "guild", "gvfs-cat", "gvfs-copy",
		"gvfs-info", "gvfs-less", "gvfs-ls", "gvfs-mime", "gvfs-mkdir",
		"gvfs-monitor-dir", "gvfs-monitor-file", "gvfs-mount", "gvfs-move",
		"gvfs-open", "gvfs-rename", "gvfs-rm", "gvfs-save",
		"gvfs-set-attribute", "gvfs-trash", "gvfs-tree", "gwenview",
		"gwenview_importer", "h2ph", "h2xs", "hardening-check", "hbpldecode",
		"hcitool", "hd", "head", "HEAD", "help2man", "helpviewer", "helpztags",
		"hexdump", "hipercdecode", "hipstopgm", "host", "hostid", "hostnamectl",
		"hp-align", "hp-check", "hp-clean", "hp-colorcal",
		"hp-config_usb_printer", "hp-doctor", "hp-firmware", "hp-hpdio",
		"hp-info", "hp-levels", "hp-logcapture", "hp-makeuri", "hp-pkservice",
		"hp-plugin", "hp-plugin-ubuntu", "hp-probe", "hp-query", "hp-scan",
		"hp-setup", "hp-testpage", "hp-timedate", "hp-unload", "i386", "ibus",
		"ibus-daemon", "ibus-setup", "ibus-table-createdb", "ical2vcal",
		"iceauth", "ico", "icontopbm", "iconv", "icotool", "icu-config",
		"icuinfo", "id", "identify", "identify.im6", "idlj", "iecset",
		"ifnames", "igawk", "ijs_pxljr", "ilbmtoppm", "im-config", "img2png",
		"img2py", "img2xpm", "imgtoppm", "im-launch", "import", "import.im6",
		"importwizard", "info", "infobrowser", "infocmp", "infokey",
		"infotocap", "inifile", "init-checkconf", "initctl2dot", "inputattach",
		"inspect", "install", "installdbgsymbols.sh", "install-info",
		"install-printerdriver", "instmodsh", "intel_audio_dump",
		"intel_backlight", "intel_bios_dumper", "intel_bios_reader",
		"intel_disable_clock_gating", "intel_dpio_read", "intel_dpio_write",
		"intel_error_decode", "intel_forcewaked", "intel_gpu_abrt",
		"intel_gpu_time", "intel_gpu_top", "intel_gtt", "intel_l3_parity",
		"intel_reg_checker", "intel_reg_dumper", "intel_reg_read",
		"intel_reg_snapshot", "intel_reg_write", "intel_sprite_on",
		"intel_stepping", "intel_upload_blit_large",
		"intel_upload_blit_large_gtt", "intel_upload_blit_large_map",
		"intel_upload_blit_small", "intel-virtual-output", "interdiff",
		"ionice", "ipcmk", "ipcrm", "ipcs", "ipod-read-sysinfo-extended",
		"ipod-time-sync", "ippfind", "ipptool", "iproxy", "iptables-xml", "irb",
		"irb1.9.1", "ischroot", "isdv4-serial-debugger",
		"isdv4-serial-inputattach", "isodump", "isohybrid", "isohybrid.pl",
		"isoinfo", "isovfy", "ispell-wrapper", "isql-vt", "isqlw-vt", "jar",
		"jarsigner", "java", "javac", "javadoc", "javah", "javap", "javaws",
		"jcmd", "jconsole", "jdb", "jexec", "jhat", "jinfo", "jmap", "join",
		"jpegtopnm", "jps", "jrunscript", "jsadebugd", "json_pp", "jstack",
		"jstat", "jstatd", "k3b", "k3bsetup", "kabc2mutt", "kabcclient",
		"kaccess", "kactivitymanagerd", "kaddressbook", "kaddressbookmigrator",
		"kapplymousetheme", "kate", "kbackgroundsnapshot", "kbdinfo",
		"kblankscrn.kss", "kbookmarkmerger", "kbuildsycoca4", "kbxutil",
		"kcalc", "kcheckrunning", "kcminit", "kcminit_startup", "kcmshell4",
		"kcm-touchpad-list-devices", "kcookiejar4", "kde4", "kde4-config",
		"kde4-menu", "kde-add-printer", "kdebugdialog", "kde-cp", "kded4",
		"kdeinit4", "kdeinit4_shutdown", "kdeinit4_wrapper", "kde-mv",
		"kde-nm-connection-editor", "kde-open", "kdepasswd", "kde-print-queue",
		"kdesudo", "kdialog", "kdostartupconfig4", "keditbookmarks",
		"keditfiletype", "kerneloops-submit", "keytool", "kfile4",
		"kfilemetadatareader", "kfontinst", "kfontview", "kglobalaccel",
		"khelpcenter", "khotnewstuff4", "khotnewstuff-upload", "kiconfinder",
		"killall", "kincidenceeditor", "kinfocenter", "kioclient",
		"kjotsmigrator", "kjs", "kjscmd", "klipper", "kmag", "kmail",
		"kmail_antivir.sh", "kmail_clamav.sh", "kmailcvt", "kmail_fprot.sh",
		"kmail-migrator", "kmail_sav.sh", "kmailservice", "kmenuedit",
		"kmimetypefinder", "kmix", "kmixctrl", "kmixremote", "kmousetool",
		"knotes", "knotes-migrator", "knotify4", "koi8rxterm", "kolourpaint",
		"konsole", "konsoleprofile", "kontact", "korgac", "korganizer",
		"kquitapp", "krandom.kss", "krdb", "krdc", "krdc_rfb_approver",
		"kreadconfig", "kres-migrator", "kross", "krunner", "kscreen-console",
		"ksendemail", "kshell4", "ksmserver", "ksnapshot", "ksplashqml",
		"ksplashsimple", "ksplashx", "ksplashx_scale", "kstart",
		"kstartupconfig4", "ksvgtopng", "ksysguard", "ksysguardd", "ksystemlog",
		"ksystraycmd", "ktelnetservice", "ktmagnetdownloader", "ktorrent",
		"ktp-contactlist", "ktp-log-viewer", "ktp-send-file", "ktraderclient",
		"ktrash", "ktupnptest", "kubuntu-debug-installer",
		"kubuntu-devel-release-upgrade", "kuiserver", "kwalletd",
		"kwalletmanager", "kwin", "kwin_gles", "kwrapper4", "kwriteconfig",
		"l2ping", "l2test", "landscape-client-ui-install", "last", "lastb",
		"lastlog", "lavadecode", "lcf", "lconvert", "ld", "ld.bfd", "ldd",
		"ld.gold", "leaftoppm", "less", "lessecho", "lessfile", "lesskey",
		"lesspipe", "lex", "lexgrog", "libnetcfg", "libpng12-config",
		"libpng-config", "libreoffice", "libtool", "libtoolize", "line",
		"linguist", "link", "lintian", "lintian-info", "linux32", "linux64",
		"linux-boot-prober", "lispmtopgm", "listres", "lnstat", "loadkeys",
		"loadunimap", "lobase", "localc", "locale", "localectl", "localedef",
		"locate", "lockfile-check", "lockfile-create", "lockfile-remove",
		"lockfile-touch", "lodraw", "loffice", "lofromtemplate", "logger",
		"logname", "loimpress", "lomath", "look", "lorder", "loweb", "lowriter",
		"lp", "lpoptions", "lppasswd", "lpq", "lpr", "lprm", "lp_solve",
		"lpstat", "lrelease", "lsattr", "lsb_release", "lscpu", "lsdiff",
		"lshw", "lsinitramfs", "lsof", "lspci", "lspgpot", "lss16toppm",
		"lsusb", "ltrace", "luit", "lupdate", "lwp-download", "lwp-dump",
		"lwp-mirror", "lwp-request", "lxterm", "lz", "lzcat", "lzcmp", "lzdiff",
		"lzegrep", "lzfgrep", "lzgrep", "lzless", "lzma", "lzmainfo", "lzmore",
		"m4", "macptopbm", "mail-lock", "mail-touchlock", "mail-unlock", "make",
		"makeconv", "makeinfo", "man", "mandb", "manhole", "manpath", "mapscrn",
		"mattrib", "mawk", "mbadblocks", "mboximporter", "mcat", "mcd",
		"mcheck", "mclasserase", "mcomp", "mcookie", "mcopy", "mc-tool",
		"mc-wait-for-name", "md5pass", "md5sum", "md5sum.textutils", "mdatopbm",
		"mdel", "mdeltree", "mdir", "mdu", "meinproc4", "meinproc4_simple",
		"memdiskfind", "mesg", "mformat", "mgrtopbm", "mimeopen", "mimetype",
		"min12xxw", "minfo", "miniterm.py", "mkdiskimage", "mkfifo",
		"mkfontdir", "mkfontscale", "mkisofs", "mkmanifest", "mk_modmap",
		"mkzftree", "mlabel", "mlocate", "mmcli", "mmd", "mmount", "mmove",
		"moc", "mogrify", "mogrify.im6", "montage", "montage.im6",
		"mousetweaks", "mpartition", "mpic++", "mpicc", "mpiCC",
		"mpicc.openmpi", "mpiCC.openmpi", "mpic++.openmpi", "mpicxx",
		"mpicxx.openmpi", "mpiexec", "mpiexec.openmpi", "mpif77",
		"mpif77.openmpi", "mpif90", "mpif90.openmpi", "mpirun",
		"mpirun.openmpi", "mrd", "mren", "mscompress", "msexpand", "msgattrib",
		"msgcat", "msgcmp", "msgcomm", "msgconv", "msgen", "msgexec",
		"msgfilter", "msgfmt", "msggrep", "msginit", "msgmerge", "msgunfmt",
		"msguniq", "mshortname", "mshowfat", "ms_print", "mtools", "mtoolstest",
		"mtr", "mtrace", "mtvtoppm", "mtype", "muon-discover", "muon-updater",
		"mxtar", "my_print_defaults", "mysql", "mysqlcheck", "mysql_install_db",
		"mysql_upgrade", "mzip", "namei", "nano", "native2ascii", "nautilus",
		"nautilus-autorun-software", "nautilus-connect-server",
		"nautilus-sendto", "nawk", "ncal", "ncurses5-config",
		"ncursesw5-config", "neotoppm", "nepomuk2-rcgen", "nepomukbackup",
		"nepomukbaloomigrator", "nepomukcleaner", "nepomukcmd", "nepomukctl",
		"nepomukfileindexer", "nepomukfilewatch", "nepomukindexer",
		"nepomukmigrator", "nepomuk-rcgen", "nepomuksearch", "nepomukserver",
		"nepomukservicestub", "nepomukshow", "nepomukstorage", "neqn", "net",
		"netkit-ftp", "newgrp", "ngettext", "nice", "nl", "nm", "nm-applet",
		"nmblookup", "nmcli", "nm-connection-editor", "nm-online", "nm-tool",
		"nohup", "notepadqq", "notify-send", "nproc", "nqq", "nroff",
		"nslookup", "nstat", "nsupdate", "ntfsdecrypt", "ntlm_auth", "numfmt",
		"nvidia-detector", "nvlc", "oakdecode", "obex-data-server", "objcopy",
		"objdump", "oclock", "od", "odbcinst", "ods-server", "okular",
		"oldfind", "oLschema2ldif", "ompi-clean", "ompi_info", "ompi-iof",
		"ompi-probe", "ompi-profiler", "ompi-ps", "ompi-server", "ompi-top",
		"omshell", "on_ac_power", "onboard", "onboard-settings",
		"oneconf-query", "online-accounts-preferences", "onto2vocabularyclass",
		"opalc++", "opalcc", "opal_wrapper", "openssl", "opldecode", "orbd",
		"orca", "orte-bootproxy", "ortec++", "ortecc", "orteCC", "orte-clean",
		"orted", "orte-iof", "orte-ps", "orterun", "orte-top",
		"orte_wrapper_script", "os-prober", "oxygen-demo", "oxygen-settings",
		"oxygen-shadow-demo", "p11-kit", "pacat", "pack200", "pacmd", "pactl",
		"padsp", "pager", "palmtopnm", "pamcut", "pamdeinterlace", "pamdice",
		"pamfile", "pamoil", "pamon", "pamstack", "pamstretch",
		"pamstretch-gen", "pango-querymodules", "pango-view", "paperconf",
		"paplay", "parec", "parecord", "parsechangelog", "partitionmanager",
		"partitionmanager-bin", "partx", "passwd", "paste", "pasuspender",
		"patch", "pathchk", "pax11publish", "pbmclean", "pbmlife", "pbmmake",
		"pbmmask", "pbmpage", "pbmpscale", "pbmreduce", "pbmtext", "pbmtextps",
		"pbmto10x", "pbmtoascii", "pbmtoatk", "pbmtobbnbg", "pbmtocmuwm",
		"pbmtoepsi", "pbmtoepson", "pbmtog3", "pbmtogem", "pbmtogo",
		"pbmtoicon", "pbmtolj", "pbmtomacp", "pbmtomda", "pbmtomgr",
		"pbmtonokia", "pbmtopgm", "pbmtopi3", "pbmtoplot", "pbmtoppa",
		"pbmtopsg3", "pbmtoptx", "pbmtowbmp", "pbmtox10bm", "pbmtoxbm",
		"pbmtoybm", "pbmtozinc", "pbmupc", "pcimodules", "pcre-config",
		"pcxtoppm", "pdb", "pdb2.7", "pdb3", "pdb3.4", "pdbedit", "pdf2dsc",
		"pdf2ps", "pdfdetach", "pdffonts", "pdfimages", "pdfinfo",
		"pdfseparate", "pdftexi2dvi", "pdftocairo", "pdftohtml", "pdftoppm",
		"pdftops", "pdftotext", "pdfunite", "peekfd", "perl", "perl5.18.2",
		"perlbug", "perldoc", "perlivp", "perlthanks", "pf2afm", "pfbtopfa",
		"pftp", "pg", "pgawk", "pgmbentley", "pgmcrater", "pgmedge",
		"pgmenhance", "pgmhist", "pgmkernel", "pgmnoise", "pgmnorm", "pgmoil",
		"pgmramp", "pgmslice", "pgmtexture", "pgmtofs", "pgmtolispm",
		"pgmtopbm", "pgmtoppm", "pgrep", "pi1toppm", "pi3topbm", "pic", "pico",
		"piconv", "pilconvert.py", "pildriver.py", "pilfile.py", "pilfont.py",
		"pilprint.py", "pimsettingexporter", "pinentry", "pinentry-gtk-2",
		"pinentry-qt4", "pinentry-x11", "pinky", "pip", "pip2", "pixeltool",
		"pjtoppm", "pkaction", "pkcheck", "pkexec", "pkg-config", "pkgdata",
		"pkill", "pkttyagent", "pl2pm", "plainbox-trusted-launcher-1",
		"plasma-desktop", "plasma-netbook", "plasma-overlay", "plasmapkg",
		"plasma-remote-helper", "plasma-windowed", "pldd", "plink", "plog",
		"pmap", "pm-is-supported", "pngtopnm", "pnm2ppa", "pnmalias",
		"pnmarith", "pnmcat", "pnmcolormap", "pnmcomp", "pnmconvol", "pnmcrop",
		"pnmcut", "pnmdepth", "pnmenlarge", "pnmfile", "pnmflip", "pnmgamma",
		"pnmhisteq", "pnmhistmap", "pnmindex", "pnminterp", "pnminterp-gen",
		"pnminvert", "pnmmargin", "pnmmontage", "pnmnlfilt", "pnmnoraw",
		"pnmnorm", "pnmpad", "pnmpaste", "pnmpsnr", "pnmquant", "pnmremap",
		"pnmrotate", "pnmscale", "pnmscalefixed", "pnmshear", "pnmsmooth",
		"pnmsplit", "pnmtile", "pnmtoddif", "pnmtofiasco", "pnmtofits",
		"pnmtojpeg", "pnmtopalm", "pnmtoplainpnm", "pnmtopng", "pnmtops",
		"pnmtorast", "pnmtorle", "pnmtosgi", "pnmtosir", "pnmtotiff",
		"pnmtotiffcmyk", "pnmtoxwd", "po2debconf", "pod2html", "pod2latex",
		"pod2latex.bundled", "pod2man", "pod2texi", "pod2text", "pod2usage",
		"podchecker", "podebconf-display-po", "podebconf-report-po",
		"podselect", "poff", "policytool", "pon", "POST", "ppdc", "ppdhtml",
		"ppdi", "ppdmerge", "ppdpo", "pphs", "ppm3d", "ppmbrighten",
		"ppmchange", "ppmcie", "ppmcolormask", "ppmcolors", "ppmdim", "ppmdist",
		"ppmdither", "ppmfade", "ppmflash", "ppmforge", "ppmhist", "ppmlabel",
		"ppmmake", "ppmmix", "ppmnorm", "ppmntsc", "ppmpat", "ppmquant",
		"ppmquantall", "ppmqvga", "ppmrainbow", "ppmrelief", "ppmshadow",
		"ppmshift", "ppmspread", "ppmtoacad", "ppmtobmp", "ppmtoeyuv",
		"ppmtogif", "ppmtoicr", "ppmtoilbm", "ppmtojpeg", "ppmtoleaf",
		"ppmtolj", "ppmtolss16", "ppmtomap", "ppmtomitsu", "ppmtompeg",
		"ppmtoneo", "ppmtopcx", "ppmtopgm", "ppmtopi1", "ppmtopict", "ppmtopj",
		"ppmtopuzz", "ppmtorgb3", "ppmtosixel", "ppmtotga", "ppmtouil",
		"ppmtowinicon", "ppmtoxpm", "ppmtoyuv", "ppmtoyuvsplit", "ppmtv", "pr",
		"precat", "preconv", "prename", "preunzip", "prezip", "prezip-bin",
		"print", "printafm", "printenv", "printerbanner", "printer-profile",
		"printf", "procan", "profiles", "prove", "proxy", "prtstat", "ps2ascii",
		"ps2epsi", "ps2pdf", "ps2pdf12", "ps2pdf13", "ps2pdf14", "ps2pdfwr",
		"ps2ps", "ps2ps2", "ps2txt", "pscp", "psed", "psfaddtable",
		"psfgettable", "psfstriptable", "psftp", "psfxtable", "psidtopgm",
		"pstopnm", "pstree", "pstree.x11", "pstruct", "ptar", "ptardiff",
		"ptargrep", "ptx", "pulseaudio", "purple-remote", "purple-send",
		"purple-send-async", "purple-url-handler", "putty", "puttygen", "pwdx",
		"pxelinux-options", "py3clean", "py3compile", "py3versions",
		"pyalacarte", "pyalamode", "pybuild", "pyclean", "pycompile", "pycrust",
		"pydoc", "pydoc2.7", "pydoc3", "pydoc3.4", "pygettext", "pygettext2.7",
		"pygettext3", "pygettext3.4", "pyhtmlizer", "python", "python2",
		"python2.7", "python2.7-config", "python2-config", "python3",
		"python3.4", "python3.4m", "python3m", "python-config", "pyversions",
		"pywrap", "pywxrc", "qapt-batch", "qapt-deb-installer", "qaptworker2",
		"qcollectiongenerator", "qdbus", "qdbuscpp2xml", "qdbusviewer",
		"qdbusxml2cpp", "qdoc", "qdoc3", "qglinfo", "qhelpconverter",
		"qhelpgenerator", "qmake", "qml", "qml1plugindump", "qmlbundle",
		"qmlimportscanner", "qmlmin", "qmlplugindump", "qmlprofiler",
		"qmlscene", "qmltestrunner", "qmlviewer", "qpdf", "qpdldecode",
		"qrttoppm", "qtchooser", "qtconfig", "qtpaths", "quassel", "quickbook",
		"quirks-handler", "qvlc", "rake1.9.1", "ranlib", "rasttopnm",
		"rawtopgm", "rawtoppm", "rcc", "rcp", "rctest", "rdiffdir", "rdoc",
		"rdoc1.9.1", "readelf", "readom", "recode-sr-latin", "recountdiff",
		"rediff", "remmina", "rename", "rename.ul", "rendercheck", "renice",
		"reset", "resize", "resizecons", "resizepart", "rev", "rfcomm",
		"rgb3toppm", "rgrep", "rhythmbox", "rhythmbox-client", "ri", "ri1.9.1",
		"rletopnm", "rlogin", "rmic", "rmid", "rmiregistry", "routef", "routel",
		"rpcclient", "rpcgen", "rpl8", "rsh", "rstart", "rstartd", "rsync",
		"rtstat", "ruby", "ruby1.9.1", "runcon", "run-mailcap",
		"run-with-aspell", "rview", "rvim", "rvlc", "s2p", "samba-regedit",
		"samba-tool", "sane-find-scanner", "savelog", "sbattach", "sbigtopgm",
		"sbkeysync", "sbsiglist", "sbsign", "sbvarsign", "sbverify",
		"scanimage", "schemagen", "scp", "scp-dbus-service", "screendump",
		"script", "scriptreplay", "sctp_darn", "sctp_status", "sctp_test",
		"sdiff", "sdptool", "seahorse", "see", "select-default-iwrap",
		"select-editor", "sendiso", "sensible-browser", "sensible-editor",
		"sensible-pager", "seq", "serialver", "servertool", "service",
		"servicemenudeinstallation", "servicemenuinstallation",
		"session-installer", "session-migration", "sessreg", "setarch",
		"setfacl", "setfattr", "setkeycodes", "setleds", "setlogcons",
		"setmetamode", "setpci", "setsid", "setterm", "setxkbmap", "sftp", "sg",
		"sgitopnm", "sha1pass", "sha1sum", "sha224sum", "sha256sum",
		"sha384sum", "sha512sum", "sharesec", "shasum", "shotwell",
		"showconsolefont", "showfont", "showkey", "showrgb", "shred", "shuf",
		"sieveeditor", "signond", "signonpluginprocess", "signon-ui",
		"simple-scan", "sirtopnm", "size", "skanlite", "skill", "slabtop",
		"sldtoppm", "slogin", "slxdecode", "smbcacls", "smbclient",
		"smbcontrol", "smbcquotas", "smbget", "smbpasswd", "smbspool",
		"smbstatus", "smbtar", "smbta-util", "smbtree", "smproxy", "snice",
		"socat", "soelim", "soffice", "software-center", "software-center-gtk3",
		"software-properties-gtk", "software-properties-kde",
		"solid-action-desktop-gen", "solid-hardware", "sopranocmd", "sopranod",
		"sort", "sotruss", "spctoppm", "spd-conf", "spd-say", "speaker-test",
		"speech-dispatcher", "splain", "split", "splitdiff", "splitfont",
		"sprof", "sputoppm", "ssh", "ssh-add", "ssh-agent", "ssh-argv0",
		"ssh-askpass", "ssh-copy-id", "ssh-import-id", "ssh-import-id-gh",
		"ssh-import-id-lp", "ssh-keygen", "ssh-keyscan", "sshvnc", "ssvnc",
		"ssvncviewer", "st4topgm", "stack_op.s", "startkde",
		"start-pulseaudio-kde", "start-pulseaudio-x11", "startx", "stat",
		"stdbuf", "strace", "stream", "stream.im6", "strings", "strip",
		"stunnel", "stunnel3", "stunnel4", "subl", "sudo", "sudoedit",
		"sudoreplay", "sum", "svc_handler.s", "svlc", "svn", "svnadmin",
		"svnauthz", "svnauthz-validate", "svn-bench", "svndumpfilter",
		"svnlook", "svnmucc", "svn-populate-node-origins-index",
		"svnraisetreeconflict", "svnrdump", "svn-rep-sharing-stats", "svnserve",
		"svnsync", "svnversion", "symcryptrun", "synclient", "syndaemon",
		"syslinux", "syslinux2ansi", "syslinux-legacy", "system-config-printer",
		"system-config-printer-applet", "systemsettings", "t1ascii", "t1asm",
		"t1binary", "t1disasm", "t1mac", "t1unmac", "tabs", "tac", "tail",
		"tap2deb", "tap2rpm", "tapconvert", "taskset", "tbl", "tclsh",
		"tclsh8.6", "tdbbackup", "tdbbackup.tdbtools", "tdbdump", "tdbrestore",
		"tdbtool", "tee", "telepathy-indicator", "telnet", "telnet.netkit",
		"test", "testlibraw", "testparm", "testrb", "testrb1.9.1", "texi2any",
		"texi2dvi", "texi2pdf", "texindex", "tgatoppm", "tgz", "thinkjettopbm",
		"thunderbird", "tic", "tifftopnm", "time", "timedatectl", "timeout",
		"tload", "tnameserv", "toc2cddb", "toc2cue", "toe", "top", "toshset",
		"totem", "totem-audio-preview", "totem-video-thumbnailer", "touch",
		"tput", "tr", "tracepath", "tracepath6", "traceroute6",
		"traceroute6.iputils", "transmission-gtk", "transset", "trial", "troff",
		"truncate", "trust", "tset", "tsort", "tst_inactivity_timer", "tsvnc",
		"ttfread", "tty", "twistd", "txixml2texi", "tzselect", "ubuntu-bug",
		"ubuntu-drivers", "ubuntu-support-status",
		"ubuntu-webapps-update-index", "ucf", "ucfq", "ucfr", "uconv",
		"ucs2any", "udisksctl", "uic", "uic3", "ul", "umax_pp",
		"unattended-upgrade", "unattended-upgrades", "unexpand", "unicode_stop",
		"uniq", "unity-control-center", "unity-scope-loader",
		"unity-settings-daemon", "unity-webapps-desktop-file",
		"unity-webapps-qml-launcher", "unity-webapps-runner", "unlink",
		"unlzma", "unopkg", "unpack200", "unrar", "unrar-nonfree", "unshare",
		"unwrapdiff", "unxz", "unzip", "unzipsfx", "update-alternatives",
		"updatedb", "updatedb.mlocate", "update-desktop-database",
		"update-gconf-defaults", "update-manager", "update-mime-database",
		"update-mime-database.real", "update-notifier",
		"update-perl-sax-parsers", "upower", "uptime", "usb-creator-gtk",
		"usb-creator-kde", "usb-devices", "usbhid-dump", "usb_printerid",
		"users", "uuidgen", "uxterm", "uz", "valgrind", "valgrind.bin",
		"valgrind-di-server", "valgrind-listener", "vcdimager", "vcd-info",
		"vcdxbuild", "vcdxgen", "vcdxminfo", "vcdxrip", "vgdb", "vi", "view",
		"viewres", "vim", "vim.basic", "vimdiff", "vim.tiny", "vimtutor",
		"vino-passwd", "vino-preferences", "virt_mail", "virtuoso-t", "vlc",
		"vlc-wrapper", "vmstat", "vmwarectrl", "vncviewer", "volname", "vstp",
		"w", "wall", "watch", "watchgnupg", "wbinfo", "wbmptopbm", "wc",
		"webapp-container", "webbrowser-app", "wftopfa", "wget", "whatis",
		"whereis", "which", "who", "whoami", "whoopsie", "whoopsie-preferences",
		"winicontoppm", "wish", "wish8.6", "withsctp", "wodim",
		"word-list-compress", "wpa_passphrase", "w.procps", "wrestool", "write",
		"wsgen", "wsimport", "X", "X11", "x11perf", "x11perfcomp", "x11vnc",
		"x86_64", "x86_64-linux-gnu-addr2line", "x86_64-linux-gnu-ar",
		"x86_64-linux-gnu-as", "x86_64-linux-gnu-c++filt",
		"x86_64-linux-gnu-cpp", "x86_64-linux-gnu-cpp-4.8",
		"x86_64-linux-gnu-dwp", "x86_64-linux-gnu-elfedit",
		"x86_64-linux-gnu-g++", "x86_64-linux-gnu-g++-4.8",
		"x86_64-linux-gnu-gcc", "x86_64-linux-gnu-gcc-4.8",
		"x86_64-linux-gnu-gcc-ar", "x86_64-linux-gnu-gcc-ar-4.8",
		"x86_64-linux-gnu-gcc-nm", "x86_64-linux-gnu-gcc-nm-4.8",
		"x86_64-linux-gnu-gcc-ranlib", "x86_64-linux-gnu-gcc-ranlib-4.8",
		"x86_64-linux-gnu-gcov", "x86_64-linux-gnu-gcov-4.8",
		"x86_64-linux-gnu-gprof", "x86_64-linux-gnu-ld",
		"x86_64-linux-gnu-ld.bfd", "x86_64-linux-gnu-ld.gold",
		"x86_64-linux-gnu-nm", "x86_64-linux-gnu-objcopy",
		"x86_64-linux-gnu-objdump", "x86_64-linux-gnu-python2.7-config",
		"x86_64-linux-gnu-python-config", "x86_64-linux-gnu-ranlib",
		"x86_64-linux-gnu-readelf", "x86_64-linux-gnu-size",
		"x86_64-linux-gnu-strings", "x86_64-linux-gnu-strip", "xargs", "xauth",
		"xbiff", "xbmtopbm", "xcalc", "xclipboard", "xclock", "xcmsdb",
		"xconsole", "xcursorgen", "xcutsel", "xdg-desktop-icon",
		"xdg-desktop-menu", "xdg-email", "xdg-icon-resource", "xdg-mime",
		"xdg-open", "xdg-screensaver", "xdg-settings", "xdg-user-dir",
		"xdg-user-dirs-gtk-update", "xdg-user-dirs-update", "xdiagnose",
		"xditview", "xdpyinfo", "xdriinfo", "xedid", "xedit", "Xephyr", "xev",
		"xeyes", "xfd", "xfontsel", "xfreerdp", "xfsinfo", "xgamma", "xgc",
		"xgettext", "xhost", "ximtoppm", "xinit", "xinput", "xjc", "xkbbell",
		"xkbcomp", "xkbevd", "xkbprint", "xkbvleds", "xkbwatch", "xkeystone",
		"xkill", "xload", "xlogo", "xlsatoms", "xlsclients", "xlsfonts", "xmag",
		"xman", "xmessage", "xml2-config", "xmlcatalog", "xmllint",
		"xmlpatterns", "xmlpatternsvalidator", "xmodmap", "xmore", "Xorg",
		"xpci", "xpmtoppm", "xprop", "xqxdecode", "xrandr", "xrandr-tool",
		"xrced", "xrdb", "xrefresh", "xrotate", "x-session-manager", "xset",
		"xsetmode", "xsetpointer", "xsetroot", "xsetwacom", "xsm", "xstdcmap",
		"xsubpp", "xterm", "x-terminal-emulator", "xtightvncviewer", "xvidtune",
		"xvinfo", "xvminitoppm", "xvncviewer", "xwd", "xwdtopnm",
		"x-window-manager", "xwininfo", "xwud", "x-www-browser", "xxd", "xz",
		"xzcat", "xzcmp", "xzdiff", "xzegrep", "xzfgrep", "xzgrep", "xzless",
		"xzmore", "yacc", "ybmtopbm", "yelp", "yes", "yuvsplittoppm",
		"yuvtoppm", "zdump", "zeisstopnm", "zeitgeist-daemon",
		"zeitgeist-datahub", "zenity", "zip", "zipcloak", "zipdetails",
		"zipgrep", "zipinfo", "zipnote", "zipsplit", "zjsdecode", "zlib-flate",
		"zsoelim" };

const char *builtinstr[] = { "cd", "help" };
vector<string> v(list, list + 2548);
vector<vector<string>> hist;
vector<string> builtin(builtinstr, builtinstr + 2);

vector<string> command::insertArg(string arg) {
	while (arg.find(" ") != string::npos) {

		table.push_back(arg.substr(0, arg.find(' ')));
		arg = arg.substr(arg.find(' ') + 1, arg.length());
	}

	table.push_back(arg);

	hist.push_back(table);
	return table;
}

void command::clearArgs() {

	table.clear();

}

void command::printArgs() {
	for (unsigned int i = 0; i < hist.size(); i++) {
		for (unsigned int j = 0; j < hist[i].size(); j++) {

			if (std::find(v.begin(), v.end(), hist[i][j]) != v.end()) {
				cout << " " << i << "  " << hist[i][j];
			}
		}
		cout << endl;
	}

}

void command::execute(vector<string> table) {

	const char **args = new const char*[table.size() + 2];
	for (unsigned int j = 0; j < table.size() + 1; ++j)
		args[j + 1] = table[j].c_str();
	args[table.size() + 1] = NULL;
	args[0] = table[0].c_str();
	pid_t cpid = fork();

	if (cpid == 0) {
		execvp(args[0], (char **) (args + 1));

	} else {

		wait(NULL);
	}

}

void scommand::initSpecial(string arg) {

	if (arg.find(">>") != string::npos) {
		outFile = arg.substr(arg.find(">>") + 3, arg.length());
		arg = arg.substr(0, arg.find(">>") - 1);
		fileStatus = 2;
	} else if (arg.find('>') != string::npos) {
		outFile = arg.substr(arg.find('>') + 2, arg.length());
		arg = arg.substr(0, arg.find('>') - 1);
		fileStatus = 1;
	}
	vector<string> table;
	while (arg.find('|') != string::npos) {
		isPipe = 1;
		table = insertArg(arg.substr(0, arg.find('|') - 1));
		sTable.push_back(table);
		clearArgs();
		arg = arg.substr(arg.find('|') + 2, arg.length());
	}
	table = insertArg(arg);
	sTable.push_back(table);

}
void scommand::setfd(int fd) {
	inFileDesc = fd;
}
int scommand::getfd() {
	return inFileDesc;
}

void scommand::execSpecial() {
	int fdout = STDOUT_FILENO;
	if (fileStatus == 1) {
		fdout = open(outFile.c_str(),
		O_RDWR | O_CREAT, S_IRWXU);
	} else if (fileStatus == 2) {
		fdout = open(outFile.c_str(),
		O_RDWR | O_CREAT | O_APPEND, S_IRWXU);
	}
	int save_out = fdout;
	save_out = fdout;
	unsigned int i = 0;
	int status;
	int filedesc;
	pid_t ret;
	for (vector<string> &table : sTable) {

		int pipefds[2];
		ret = pipe(pipefds);

		if (ret == -1) {
			perror("broken pipe\n");
			exit(-1);
		}
		const char **args = new const char*[table.size() + 2];
		for (unsigned int j = 0; j < table.size() + 1; ++j)     // copy args
			args[j + 1] = table[j].c_str();
		args[table.size() + 1] = NULL;
		args[0] = table[0].c_str();
		filedesc = getfd();
		save_out = dup(STDOUT_FILENO);
		pid_t cpid = fork();
		if (cpid == 0) {
			if (i == sTable.size() - 1) {

				dup2(fdout, STDOUT_FILENO);
				dup2(filedesc, STDIN_FILENO);
			} else if (i == 0) {
				dup2(pipefds[1], STDOUT_FILENO);

			} else {
				dup2(filedesc, STDIN_FILENO);
				dup2(pipefds[1], STDOUT_FILENO);
			}
			if (execvp(args[0], (char **) (args + 1)) == -1) {
				exit(-1); // If child fails

			}
		}
		waitpid(cpid, &status, WUNTRACED | WCONTINUED);

		if (i != 0)
			close(getfd());
		close(pipefds[1]);
		if (i == sTable.size() - 1) {
			close(pipefds[0]);
		}
		dup2(save_out, STDOUT_FILENO);
		setfd(pipefds[0]);
		i++;

	}
}

void command::builtin(string arg) {
	int i;
	int l = sizeof(builtinstr) / sizeof(char *);
	if (arg.substr(0, arg.find(' ')) == "cd") {
		string dir = arg.substr(arg.find(' ') + 1, arg.length());
		if (dir.c_str() == NULL) {
			fprintf(stderr, "Expected argument to \"cd\"\n");
		} else {
			if (chdir(dir.c_str()) != 0) {
				perror("cd failed");
			}
		}

	} else if (arg == "help") {

		printf("--------------Sumanth Murali's Shell----------------\n");
		printf("Type program names and arguments, and hit enter.\n");
		for (i = 0; i < l; i++) {
			printf("\t%s\n", builtinstr[i]);
		}

		printf("Use man command for information on other programs.\n");

	}

}
