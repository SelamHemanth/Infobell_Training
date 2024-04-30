# CGROUPS
---

 * A cgroup is a logical grouping of processes that can be used for resource management in the kernel. Once a cgroup has been created, processes can be migrated in and out of the cgroup via a pseudo-filesystem API.
 * See all the Cgroups:
```javascript
 $ cat /proc/cgroups

#subsys_name    hierarchy       num_cgroups     enabled
cpuset  6       1       1
cpu     5       130     1
cpuacct 5       130     1
blkio   11      130     1
memory  8       248     1
devices 12      130     1
freezer 4       8       1
net_cls 2       1       1
perf_event      3       1       1
net_prio        2       1       1
hugetlb 7       1       1
pids    9       142     1
rdma    10      1       1

 $ lssubsys        // sudo apt install cgroup-tools

cpuset
cpu,cpuacct
blkio
memory
devices
freezer
net_cls,net_prio
perf_event
hugetlb
pids
rdma
```
 * The CPU controller mechanism allows a system manager to control the percentage of CPU time given to a cgroup. The CPU controller can be used both to guarantee that a cgroup gets a guaranteed minimum percentage of CPU on the system, regardless of other load on the system, and also to set an upper limit on the amount of CPU time used by a cgroup, so that a rogue process can't consume all of the available CPU time.
 * CPU scheduling is first of all done at the cgroup level, and then across the processes within each cgroup. As with some other controllers, CPU cgroups can be nested, so that the percentage of CPU time allocated to a top-level cgroup can be further subdivided across cgroups under that top-level cgroup.
 * The memory controller mechanism can be used to limit the amount of memory that a process uses. If a rogue process runs over the limit set by the controller, the kernel will page out that process, rather than some other process on the system..
 * `Systemd` can specify cgroup parameters when launching services at boot!
```javascript
 $ man systemd.resource-control
```
 
Note: For more details, please go through [`CGroup`](https://github.com/SelamHemanth/Infobell_Training/blob/main/22-4-2024/InfobellIT_LinuxKernel_Apr2024_kaiwanTECH_6d/courseware/mod08_task_scheduler/cgroups.pdf) document.

***Kernel Synchronising Locking***
---

 * 
