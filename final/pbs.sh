#PBS -l nodes=10:ppn=12,walltime=01:00:00
#PBS -q batch
#PBS -N arnaudoc
#PBS -j oe
#PBS -V

#cat $PBS_NODEFILE
cd ~/final

for i in 1 2 4 8; do
   for j in 1 2 4 8; do
    mpiexec -np $i --map-by ppr:$j:node --hostfile $PBS_NODEFILE final.cx
    done
done