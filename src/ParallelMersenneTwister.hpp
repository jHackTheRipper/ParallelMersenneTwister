/*
 *  ParallelMersenneTwister.hpp
 *  
 *
 *  Created by Jonathan PASSERAT-PALMBACH on 5/15/12 following
 *  Luc TOURAILLE's advice.
 *  Copyright 2012 ISIMA/LIMOS. All rights reserved.
 *
 */

#ifndef PARALLEL_MERSENNE_TWISTER
#define PARALLEL_MERSENNE_TWISTER


/** ParallelMersenneTwister is a wrapper class that enables polymorphism
   within the hierarachy of independant MersenneTwister parameters set.
 */
template <typename T>
struct ParallelMersenneTwister {
   
   typedef T result_type;
      
   // make it compliant with boost to enable distributions
   virtual result_type next() = 0;
   virtual result_type operator()() = 0;
   virtual result_type min() = 0;
   virtual result_type max() = 0;
   
};


/** Concrete implementation of the PRNG.
   Instances will differ from each other by the MT parameter: i.e. the independent
   Mersenne Twister model.
 */
template <typename T, class MT>
class ParallelMersenneTwister_impl : public ParallelMersenneTwister<T> {
   MT gen_;
   
public:
   T next() {
      return gen_();
   }
   
   T operator()() {
      return gen_();
   }
   
   T min() {
      return gen_.min();
   }   
   
   T max() {
      return gen_.max();
   }
};

#include <mersenneTwister_instances.hpp>

/** This function enables threads to pick up the independent instance of MT
    corresponding to their unique identifier.
   @param threadIdx The calling thread's unique identifier.
   @return A pointer to the independent MT instance assigned to the calling thread.
 */
template <typename T>
ParallelMersenneTwister<T>* getParallelMersenneTwister(unsigned int threadIdx) {
   return MTParametersArray<T>::generators[threadIdx];
}



#endif // PARALLEL_MERSENNE_TWISTER