// Copyright 2010-2021, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifdef OS_WIN
#include <windows.h>
#endif  // OS_WIN

#include <QGuiApplication>
#include <QtGui>

#include "base/logging.h"
#include "base/process_mutex.h"
#include "base/system_util.h"
#include "gui/base/util.h"
#include "gui/post_install_dialog/post_install_dialog.h"

#ifdef OS_WIN
#include "base/win_util.h"
#endif  // OS_WIN

int RunPostInstallDialog(int argc, char *argv[]) {
  Q_INIT_RESOURCE(qrc_post_install_dialog);

  mozc::SystemUtil::DisableIME();

  std::string name = "post_install_dialog.";
  name += mozc::SystemUtil::GetDesktopNameAsString();

  mozc::ProcessMutex mutex(name.c_str());
  if (!mutex.Lock()) {
    LOG(INFO) << "post_install_dialog is already running";
    return -1;
  }

#ifdef OS_WIN
  // For ImeUtil::SetDefault.
  mozc::ScopedCOMInitializer com_initializer;
#endif  // OS_WIN

  auto app = mozc::gui::GuiUtil::InitQt(argc, argv);

  mozc::gui::GuiUtil::InstallTranslator("post_install_dialog");

  mozc::gui::PostInstallDialog dialog;
  dialog.exec();

  return 0;
}
