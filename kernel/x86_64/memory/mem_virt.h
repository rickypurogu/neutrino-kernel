#pragma once
#include "paging.h"
#include <stdint.h>
#include <size_t.h>
#include <stdbool.h>
#include <libs/limine/stivale2.h>
#include <libs/neutrino/lock.h>

struct memory_virtual {
    uint8_t address_size; 
    bool initialized;
};

struct memory_virtual vmm;

extern Lock vmm_lock;

void init_vmm();
void init_vmm_on_ap(struct stivale2_smp_info* info);

bool vmm_unmap_page(PageTable* table, uintptr_t virt_addr);
void vmm_map_page(PageTable* table, uintptr_t phys_addr, uintptr_t virt_addr, PageProperties prop);

uintptr_t vmm_allocate_memory(PageTable* table, size_t blocks, PageProperties prop);
uintptr_t vmm_allocate_heap(size_t blocks, bool user);
uintptr_t vmm_map_mmio(uintptr_t mmio_addr, size_t blocks);
bool vmm_free_memory(PageTable* table, uintptr_t addr, size_t blocks);

PageTable* NewPageTable();
void DestroyPageTable(PageTable* page_table);
void vmm_switch_space(PageTable* page_table);
