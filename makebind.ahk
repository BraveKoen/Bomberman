#singleinstance
#persistent
#noenv

#z:: run_make()
#+z:: run_make(,, "max")
#^z:: run_make(, "rebuild")
#^+z:: run_make(, "rebuild", "max")

run_make(script := "makerun.cmd", options := "", window_size := "") {
    save_active_file()
    static pid
    WinClose, % "ahk_pid" . pid
    Run, % script . " " . options, % A_ScriptDir, % window_size, pid
}

save_active_file(editor_class := "PX_WINDOW_CLASS") {
    if (WinActive(A_ScriptDir . "ahk_class" . editor_class)) {
        SendInput, ^{s}
    }
}
