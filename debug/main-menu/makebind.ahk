#singleinstance
#persistent
#noenv

#z:: run_make()
#^z:: run_make(, "rebuild")

run_make(script := "makerun.cmd", options := "") {
    static pid
    WinClose, % "ahk_pid" . pid
    Run, % script . " " . options, % A_ScriptDir,, pid
}
