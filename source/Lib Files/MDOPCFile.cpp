void _DetectRealCDDrive() {
    
    return;
}

void _GXInitFileSystem() {

    return;
}

void _GXCloseFileSystem(void) {

    return;
}

void __cdecl _GXFileRename(HFILE param_1,LONG param_2,short param_3) {

  _llseek(param_1,param_2,(int)param_3);
  return;
}
