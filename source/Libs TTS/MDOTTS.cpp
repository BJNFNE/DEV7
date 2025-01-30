void TTSResume(int param_1) {

  if (param_1 != 0) {
    TTSVoice::SetAudioParams(param_1);
    return;
  }
  return;
}