
// Copyright (C) Force67 2019

#include "object.h"
#include "kern/proc.h"
#include "util/object_table.h"

#include <logger/logger.h>

namespace krnl {
kObject::kObject(proc *process, oType type) : otype(type), process(process) {
  uint32_t temp = 0;
  process->getObjTable().add(this, temp);

  std::printf("-> NEW HANDLE %d", temp);
}

void kObject::release() {
  if (--refCount == 0)
    delete this;
}

void kObject::retain() { refCount++; }

void kObject::retainHandle() {
  process->getObjTable().keep(handleCollection[0]);
}

void kObject::releaseHandle() {
  process->getObjTable().release(handleCollection[0]);
}
} // namespace krnl