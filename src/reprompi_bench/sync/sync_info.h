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

#ifndef REPROMPI_SYNC_PARSE_OPTIONS_H_
#define REPROMPI_SYNC_PARSE_OPTIONS_H_

#include <getopt.h>


enum {
    FLAG_START_TIME_HAS_PASSED = 0x1,
    FLAG_SYNC_WIN_EXPIRED = 0x2
};

typedef struct {
    double window_size_sec; /* --window-size */
    int n_fitpoints; /* --fitpoints */
    int n_exchanges; /* --exchanges */

    double wait_time_sec; /* --wait-time */
} reprompib_sync_options_t;


typedef enum reprompi_win_sync_getopt_ids {
  REPROMPI_ARGS_WINSYNC_WIN_SIZE = 700,
  REPROMPI_ARGS_WINSYNC_NFITPOINTS,
  REPROMPI_ARGS_WINSYNC_NEXCHANGES,
  REPROMPI_ARGS_WINSYNC_WAITTIME
} reprompi_win_sync_getopt_ids_t;

extern const struct option reprompi_sync_long_options[];
extern const char reprompi_sync_opts_str[];


void reprompi_init_sync_parameters(reprompib_sync_options_t* opts_p);

#endif /* REPROMPI_SYNC_PARSE_OPTIONS_H_ */
