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

#ifndef INCLUDED_CXXRTL_SIM_H
#define INCLUDED_CXXRTL_SIM_H

#include <cxxrtl/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace cxxrtl {

    /*!
     * \brief <+description of block+>
     * \ingroup cxxrtl
     *
     */
    class CXXRTL_API sim : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<sim> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of cxxrtl::sim.
       *
       * To avoid accidental use of raw pointers, cxxrtl::sim's
       * constructor is in a private implementation
       * class. cxxrtl::sim::make is the public interface for
       * creating new instances.
       */
      static sptr make();
    };

  } // namespace cxxrtl
} // namespace gr

#endif /* INCLUDED_CXXRTL_SIM_H */

