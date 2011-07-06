###
### Credits:
###       Marc Gauthier <marc@tensilica.com>
###	  Pete Delaney <piet@tensilica.com>
###
###  Shows memory PTE's, also provids some usefull macros 
###  for getting the current task pointer
###

define show_mem_pte
    set $vaddr = (unsigned long) $arg0
    if ($argc > 1)
   	set $task = (struct task_struct *) $arg1
    else
#	Calculates: $current, $mm, $pgd, $pgd_table
	get_current
	set $task = $current
    end	

    printf "Displaying pte for task:0x%08x mapping vaddr:0x%08x\n", $task, $vaddr

    set $pgd_index = (($vaddr >> 22) & 0x3FF)
    set $pgd_offset = (($vaddr >> 22) & 0x3FF) * 4
    set $pte_index = (($vaddr >> 12) & 0x3FF)
    set $pte_offset = (($vaddr >> 12) & 0x3FF) * 4
    set $page_offset = ($vaddr & 0xFFF)

    printf " pgd_offset:0X%08x:%d,\t", $pgd_offset, $pgd_offset
    printf "pgd_index:0X%08x:%d\n", $pgd_index, $pgd_index

    printf " pte_offset:0X%08x:%d, \t", $pte_offset, $pte_offset
    printf "pte_index:0X%08x:%d\n", $pte_index, $pte_index

    printf "page_offset:0X%08x:%d\n\n", $page_offset, $page_offset

    set $pgd_table = *((pgd_table_t *) $pgd)
    set $pmd = (pmd_t *) (((long) $pgd) + $pgd_offset)

    printf "$pmd:0x%08x =  (pmd_table_t *) (((long *) $pgd:0x%08x) + $pgd_offset:0x%08x )\n", $pmd, $pgd, $pgd_offset
    printf "*$pmd:\n"
    print *$pmd

    set $pte_table = $pmd->pud.pgd.page_table
    printf "$pte_table:0x%08x  = $pmd->pud.pgd.page_table\n", $pte_table
    print $pte_table

    set $pte = &($pte_table->pte[$pte_index])

    printf "$pte = 0x%08x = &($pte_table->pte[pte_index:%d])\n", $pte, $pte_index

    printf "*$pte:\n"
    print *$pte

end
document show_mem_pte
  Show the physical memory copy of PTE entry for the specified virtual address.
  Shows both how it appears in the cache and uncached memory.
  Usage: show_mem_pte <virtual_address> [ <task-pointer> ]
end

define get_current
    if $argc > 0
	set $stackptr = $arg0
    else
	set $stackptr = $sp
    end
    set $stackmask = ~(thread_size - 1)
    set $taskbase = ($stackptr & $stackmask)
    set $tinfo = (struct thread_info*)$taskbase	
    set $current = $tinfo->task
    printf "$current = 0x%x\n", $current
    if $current != 0
	if $current->mm != 0
	   set $mm = $current->mm
	else
	  if $current->active_mm
	    set $mm = $current->active_mm
	  end
	end
	printf "$mm = 0x%x\n", $mm
	if $mm
#	   set $pgd_dir   = (pgd_dir_t *) $mm->pgd
	   set $pgd = (pgd_t *) $mm->pgd
	   set $pgd_table = (pgd_table_t *) $mm->pgd
#	   printf "$pgd_dir = 0x%x\n", $pgd_dir
	   printf "$pgd_table = 0x%x\n", $pgd_table
	end
    end
end
document get_current
  Get current task pointer
  Usage: get_current [optional-stack-pointer]
end

define current
    if $argc > 0
	get_current $arg0
    else
        get_current
    end
end
document current
  Shorthand for get_current
  Usage: current [optional-stack-pointer]
end

define vmap
    if $argc > 1
	get_current $arg1
    else
        get_current
    end

    show_mem_pte $arg0 $current
end
document vmap
  Show the physical memory copy of PTE entry for the specified virtual address.
  Usage: vmap <virtual_address> [<stack-pointer>]
end

