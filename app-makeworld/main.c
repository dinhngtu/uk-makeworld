#include <stdio.h>
#include <errno.h>
#include <uk/essentials.h>
#include <uk/plat/lcpu.h>
#include <uk/alloc.h>

void myfunc(struct __regs *regs __unused, void *arg __unused) {
        printf("Hello from %ld %d\n", ukplat_lcpu_id(), ukplat_lcpu_idx());
}

void myfunc2(struct __regs *regs __unused, void *arg __unused) {
        printf("Super! %ld %d\n", ukplat_lcpu_id(), ukplat_lcpu_idx());
}

int main(int argc __unused, char *argv[] __unused)
{
        struct uk_alloc *a = uk_alloc_get_default();
        __lcpuidx idx[] = {1, 2};
        void *stack[] = {a->palloc(a, 8) + 8 * __PAGE_SIZE,
                         a->palloc(a, 8) + 8 * __PAGE_SIZE};
        struct ukplat_lcpu_func fn = {myfunc, NULL};
        struct ukplat_lcpu_func fn2 = {myfunc2, NULL};
        unsigned int num = sizeof(idx) / sizeof(__lcpuidx);
        int rc;

        rc = ukplat_lcpu_start(idx, &num, stack,
                               NULL, 0);
        if (unlikely(rc))
                uk_pr_err("Failed start: %d\n", rc);

        rc = ukplat_lcpu_wait(NULL, 0, 0);
        if (unlikely(rc))
                uk_pr_err("Failed wait: %d\n", rc);

        rc = ukplat_lcpu_run(NULL, 0, &fn, 0);
        if (unlikely(rc))
                uk_pr_err("Failed run: %d\n", rc);

        rc = ukplat_lcpu_run(NULL, 0, &fn2, 0);
        if (unlikely(rc))
                uk_pr_err("Failed run: %d\n", rc);

        rc = ukplat_lcpu_wait(NULL, 0, 0);
        if (unlikely(rc))
                uk_pr_err("Failed wait: %d\n", rc);

        return 0;
}
