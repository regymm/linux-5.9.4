/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Regents of the University of California
 */


#ifndef _ASM_RISCV_IRQFLAGS_H
#define _ASM_RISCV_IRQFLAGS_H

#include <asm/processor.h>
#include <asm/csr.h>

/* read interrupt enabled status */
static inline unsigned long arch_local_save_flags(void)
{
	return csr_read(CSR_STATUS);
}

/* unconditionally enable interrupts */
extern void _quasi_uart_putstr(const char*);
extern void _quasi_uart_putchar(char);
static inline void arch_local_irq_enable(void)
{
	//_quasi_uart_putstr("local_irq_enable\r\n");
	csr_set(CSR_STATUS, SR_IE);
}

/* unconditionally disable interrupts */
static inline void arch_local_irq_disable(void)
{
	csr_clear(CSR_STATUS, SR_IE);
}

/* get status and disable interrupts */
static inline unsigned long arch_local_irq_save(void)
{
	return csr_read_clear(CSR_STATUS, SR_IE);
}

/* test flags */
static inline int arch_irqs_disabled_flags(unsigned long flags)
{
	return !(flags & SR_IE);
}

/* test hardware interrupt enable bit */
static inline int arch_irqs_disabled(void)
{
	return arch_irqs_disabled_flags(arch_local_save_flags());
}

/* set interrupt enabled status */
static inline void arch_local_irq_restore(unsigned long flags)
{
	//_quasi_uart_putstr("local_irq_restore");
	//_quasi_uart_putchar('0' + (flags & SR_PIE));
	//_quasi_uart_putchar('0' + (flags & SR_IE));
	//_quasi_uart_putstr("\r\n");
	csr_set(CSR_STATUS, flags & SR_IE);
}

#endif /* _ASM_RISCV_IRQFLAGS_H */
