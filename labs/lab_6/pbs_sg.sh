#PBS -l nodes=2:ppn=12,walltime=00:00:10
#PBS -q batch
#PBS -N run_mpisg
#PBS -j oe
#PBS -V

#cat $PBS_NODEFILE
cd /home/arnaudoc/lab_6/
mpiexec -np 2 --map-by ppr:1:node --hostfile $PBS_NODEFILE ./mpisg.cx
