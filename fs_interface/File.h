#pragma once
#ifndef MESSMER_FSPP_FSINTERFACE_FILE_H_
#define MESSMER_FSPP_FSINTERFACE_FILE_H_

#include "Node.h"
#include <messmer/cpp-utils/pointer/unique_ref.h>

namespace fspp {
class Device;
class OpenFile;

class File: public virtual Node {
public:
  virtual ~File() {}

  virtual cpputils::unique_ref<OpenFile> open(int flags) const = 0;
  virtual void truncate(off_t size) const = 0;
};

}

#endif
