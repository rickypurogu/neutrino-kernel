#include "context.h"
#include "../sse.h"
#include "../memory/mem_virt.h"
#include "kernel/common/memory/memory.h"
#include "kernel/common/tasks/context.h"
#include "kernel/common/tasks/task.h"
#include "kernel/common/kservice.h"
#include <liballoc.h>

// === PRIVATE FUNCTIONS ========================

// === PUBLIC FUNCTIONS =========================

// *Create a new Context
Context* NewContext() {
    Context* context = (Context*)kmalloc(sizeof(Context));
    context->simd = (uint8_t*)kmalloc(get_sse_context_size());
    set_initial_sse_context(context->simd);
    return context;
}

// *Destroy a Context and deallocate its resources
// @param context the pointer to the Context to be destroyed
void DestroyContext(Context* context) {
    kfree(context);
}

void volatile_fun context_init(Context* context, uintptr_t ip, uintptr_t sp, uintptr_t ksp, ContextFlags cflags) {
    Registers regs;

    regs.rip = ip;
    regs.rflags = RFLAGS_INTERRUPT_ENABLE | RFLAGS_RESERVED1_ONE;
    
    if (IsUserTask(cflags)) {
        // todo implement userspace
    } else {
        regs.cs = 0x18; // code selector
        regs.ss = 0x20; // data selector
        regs.rbp = PROCESS_STACK_BASE;
    }

    regs.rsp = (uint64_t)sp;
    context->regs = regs;
    // context->syscall_kstack = ksp; // todo implement syscalls
}

void context_save(Context* context, const Registers* regs) {
    save_sse_context(context->simd);
    context->regs = *regs;
}

void context_load(Context* context, Registers* regs) {
    *regs = context->regs;
    load_sse_context(context->simd);
}
