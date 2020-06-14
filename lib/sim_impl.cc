/* -*- c++ -*- */
/*
 * Copyright 2020 gr-cxxrtl author.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "sim_impl.h"

#include <backends/cxxrtl/cxxrtl_vcd.h>

using namespace cxxrtl;

namespace gr {
  namespace cxxrtl {

    sim::sptr
    sim::make()
    {
      return gnuradio::get_initial_sptr
        (new sim_impl());
    }


    /*
     * The private constructor
     */
    sim_impl::sim_impl()
      : gr::block("sim",
              gr::io_signature::make(1, 1, sizeof(std::complex<float>)),
              gr::io_signature::make(1, 1, sizeof(float)))
    {
	  //// Dump a VCD for testing
	  //debug_items all_debug_items;
	  //top.debug_info(all_debug_items);

	  //vcd_writer vcd;
	  //vcd.timescale(1, "us");
	  //vcd.add_without_memories(all_debug_items);
	
	  //std::ofstream waves("waves.vcd");
	  //top.step();
	  //vcd.sample(0);
	  //float phase = 0;
	  //for (int steps=0; steps < 1000; steps++) {
	  //  top.p_input__i = value<16>{int16_t(cos(phase) * 16384.0)};
	  //  top.p_input__q = value<16>{int16_t(sin(phase) * 16384.0)};
	  //  top.p_clk = value<1>{0u};
	  //  top.step();
	  //  vcd.sample(steps*2 + 0);

	  //  top.p_clk = value<1>{1u};
	  //  top.step();
	  //  vcd.sample(steps*2 + 1);
	  //  waves << vcd.buffer;
	  //  vcd.buffer.clear();
	  //  phase += 0.01;
	  //}
	}

    /*
     * Our virtual destructor.
     */
    sim_impl::~sim_impl()
    {
    }

    void
    sim_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
      ninput_items_required[0] = noutput_items;
    }

    int
    sim_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const std::complex<float> *in = (const std::complex<float> *) input_items[0];
      float *out = (float *) output_items[0];

	  for (int i = 0; i < noutput_items; i++) {
		top.p_input__i = value<16>{int16_t(in[i].real() * 16384.0)};
		top.p_input__q = value<16>{int16_t(in[i].imag() * 16384.0)};

		top.p_clk = value<1>{0u};
		top.step();
		top.step();
		top.p_clk = value<1>{1u};
		top.step();
		top.step();

		out[i] = int16_t(top.p_output.data[0]) / 32768.0;
	  }

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace cxxrtl */
} /* namespace gr */

