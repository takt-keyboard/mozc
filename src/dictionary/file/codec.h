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

// Defines codec for dictionary file

#ifndef MOZC_DICTIONARY_FILE_CODEC_H_
#define MOZC_DICTIONARY_FILE_CODEC_H_

#include <cstdint>
#include <iosfwd>
#include <string>
#include <vector>

#include "base/port.h"
#include "dictionary/file/codec_interface.h"
#include "dictionary/file/section.h"
#include "absl/status/status.h"

namespace mozc {
namespace dictionary {

class DictionaryFileCodec : public DictionaryFileCodecInterface {
 public:
  DictionaryFileCodec();

  DictionaryFileCodec(const DictionaryFileCodec &) = delete;
  DictionaryFileCodec &operator=(const DictionaryFileCodec &) = delete;

  ~DictionaryFileCodec() override;

  void WriteSections(const std::vector<DictionaryFileSection> &sections,
                     std::ostream *ofs) const override;
  absl::Status ReadSections(
      const char *image, int length,
      std::vector<DictionaryFileSection> *sections) const override;
  std::string GetSectionName(const std::string &name) const override;

 private:
  void WriteHeader(std::ostream *ofs) const;
  void WriteSection(const DictionaryFileSection &section,
                    std::ostream *ofs) const;

  // Seed value for name string finger print
  // Made it mutable for reading sections.
  mutable int32_t seed_;
  // Magic value for simple file validation
  const int32_t filemagic_;
};

}  // namespace dictionary
}  // namespace mozc

#endif  // MOZC_DICTIONARY_FILE_CODEC_H_
