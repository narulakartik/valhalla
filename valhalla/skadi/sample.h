#ifndef __VALHALLA_SAMPLE_H__
#define __VALHALLA_SAMPLE_H__

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>

#include <valhalla/midgard/sequence.h>

namespace valhalla {
  namespace skadi {

    class sample{
     public:
      //non-default-constructable and non-copyable
      sample() = delete;
      sample(sample&&) = default;
      sample& operator=(sample&&) = default;
      sample(const sample&) = delete;
      sample& operator=(const sample&) = delete;

      /**
       * Constructor
       * @param data_source  directory name of the datasource from which to sample
       */
      sample(const std::string& data_source);

      /**
       * Get a single sample from the datasource
       * @param coord  the single posting at which to sample the datasource
       */
      template <class coord_t>
      double get(const coord_t& coord) const;

      /**
       * Get multiple samples from the datasource
       * @param coords  the list of postings at which to sample the datasource
       */
      template <class coords_t>
      std::vector<double> get_all(const coords_t& coords) const;

      /**
       * @return the no data value for this data source
       */
      double get_no_data_value() const;

     protected:

      /**
       * @param  index  the index of the data tile being requested
       * @return the array of data or nullptr if there was none
       */
      const int16_t* source(uint16_t index) const;

      //using memory maps
      enum class format_t{ UNKNOWN = 0, GZIP = 1, LZ4HC = 2, RAW = 3 };
      std::vector<std::pair<format_t, midgard::mem_map<char> > > mapped_cache;

      //TODO: make an LRU
      using unzipped_t = std::pair<int16_t, std::vector<int16_t> >;
      mutable unzipped_t unzipped;
    };

  }
}


#endif //__VALHALLA_SAMPLE_H__
