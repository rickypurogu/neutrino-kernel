#pragma once
#include "paging.h"
#include <stdint.h>
#include <size_t.h>
#include <stdbool.h>
#include <libs/limine/stivale2.h>

struct memory_virtual {
    uint8_t address_size; 
};

struct memory_virtual vmm;

void init_vmm();
void init_vmm_on_ap(struct stivale2_smp_info* info);

bool vmm_unmap_page(PageTable* table, uintptr_t virt_addr);
void vmm_map_page(PageTable* table, uintptr_t phys_addr, uintptr_t virt_addr, bool writable, bool user);

uintptr_t vmm_allocate_memory(PageTableEntry* table, size_t blocks, bool writable, bool user);
bool vmm_free_memory(PageTableEntry* table, uintptr_t addr, size_t blocks);
uintptr_t vmm_map_mmio(uintptr_t mmio_addr, size_t blocks);

PageTable* NewPageTable();
void DestroyPageTable(PageTable* page_table);
void vmm_switch_space(PageTable* page_table);
