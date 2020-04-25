#ifndef LIB_UTILS
#define LIB_UTILS

/**
 * Utils.
 */
class Utils {
  public:

    /**
     * Get array length.
     *
     * @param x Array.
     * @return Input array length.
     */
    template <typename T> unsigned static long arrayLen(T * x) {
      return sizeof(x) / sizeof(x[0]);
    }
};

#endif
