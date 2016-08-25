/*  ReproMPI Benchmark
 *
 *  Copyright 2015 Alexandra Carpen-Amarie, Sascha Hunold
    Research Group for Parallel Computing
    Faculty of Informatics
    Vienna University of Technology, Austria

<license>
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
</license>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"
#include "collectives.h"


/***************************************/
// MPI_Reduce_Scatter_block with MPI_Reduce and MPI_Scatter
inline void execute_GL_Reduce_scatter_block_as_ReduceScatter(collective_params_t* params) {

    MPI_Reduce(params->sbuf, params->tmp_buf, params->scount, params->datatype,
                params->op, params->root, MPI_COMM_WORLD);
    MPI_Scatter(params->tmp_buf, params->rcount, params->datatype,
               params->rbuf, params->rcount, params->datatype,
               params->root, MPI_COMM_WORLD);

}


void initialize_data_GL_Reduce_scatter_block_as_ReduceScatter(const basic_collective_params_t info, const long msize, collective_params_t* params) {
    initialize_common_data(info, params);

    params->msize = msize; // size of the block received by each process after scatter

    params->scount = msize * params->nprocs;
    params->rcount = msize;

    params->sbuf = (char*) malloc(params->scount * params->datatypesize);
    params->rbuf = (char*) malloc(params->rcount * params->datatypesize);

    params->tmp_buf = (char*) malloc(params->scount * params->datatypesize);

}


void cleanup_data_GL_Reduce_scatter_block_as_ReduceScatter(collective_params_t* params) {
    free(params->sbuf);
    free(params->rbuf);
    free(params->tmp_buf);
    params->sbuf = NULL;
    params->rbuf = NULL;
    params->tmp_buf = NULL;

}
/***************************************/



/***************************************/
// MPI_Reduce_scatter with MPI_Allreduce
inline void execute_GL_Reduce_scatter_as_Allreduce(collective_params_t* params) {
    MPI_Allreduce(params->sbuf, params->tmp_buf, params->scount, params->datatype,
               params->op, MPI_COMM_WORLD);

#ifdef COMPILE_BENCH_TESTS
   memcpy((char*)params->rbuf, (char*)params->tmp_buf + params->rank * params->msize * params->datatypesize,
           params->msize * params->datatypesize);
#endif
}


void initialize_data_GL_Reduce_scatter_as_Allreduce(const basic_collective_params_t info, const long msize, collective_params_t* params) {
    initialize_common_data(info, params);

    params->msize = msize; // size of the block received by each process after scatter

    params->scount = msize * params->nprocs;
    params->rcount = msize;

    params->sbuf = (char*) malloc(params->scount * params->datatypesize);
    params->rbuf = (char*) malloc(params->rcount * params->datatypesize);

    params->tmp_buf = (char*) malloc(params->scount * params->datatypesize);

}


void cleanup_data_GL_Reduce_scatter_as_Allreduce(collective_params_t* params) {
    free(params->sbuf);
    free(params->rbuf);
    free(params->tmp_buf);
    params->sbuf = NULL;
    params->rbuf = NULL;

}
/***************************************/


/***************************************/
// MPI_Reduce_Scatter with MPI_Reduce and MPI_Scatterv
inline void execute_GL_Reduce_scatter_as_ReduceScatterv(collective_params_t* params) {

    MPI_Reduce(params->sbuf, params->tmp_buf, params->scount, params->datatype,
                params->op, params->root, MPI_COMM_WORLD);
    MPI_Scatterv(params->tmp_buf, params->counts_array, params->displ_array, params->datatype,
               params->rbuf, params->rcount, params->datatype,
               params->root, MPI_COMM_WORLD);

}

void initialize_data_GL_Reduce_scatter_as_ReduceScatterv(const basic_collective_params_t info, const long msize, collective_params_t* params) {
    int i;

    initialize_common_data(info, params);

    params->msize = msize; // size of the block received by each process after scatter

    params->scount = msize * params->nprocs;
    params->rcount = msize;

    params->sbuf = (char*) malloc(params->scount * params->datatypesize);
    params->rbuf = (char*) malloc(params->rcount * params->datatypesize);

    params->tmp_buf = (char*) malloc(params->scount * params->datatypesize);

    // we send the same number of elements (msize) to all processes
    params->counts_array = (int*) malloc(params->nprocs * sizeof(int));
    params->displ_array = (int*) malloc(params->nprocs * sizeof(int));

    params->counts_array[0] = msize;
    params->displ_array[0] = 0;
    for (i=1; i< params->nprocs; i++) {
        params->counts_array[i] = msize;
        params->displ_array[i] = params->displ_array[i-1] + params->counts_array[i-1];
    }
}


void cleanup_data_GL_Reduce_scatter_as_ReduceScatterv(collective_params_t* params) {
    free(params->sbuf);
    free(params->rbuf);
    free(params->tmp_buf);

    free(params->counts_array);
    free(params->displ_array);
    params->sbuf = NULL;
    params->rbuf = NULL;
    params->tmp_buf = NULL;
    params->counts_array = NULL;
    params->displ_array = NULL;

}
/***************************************/
