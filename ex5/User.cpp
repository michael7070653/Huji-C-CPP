#include "User.h"
#include "RecommendationSystem.h"
#include <string>
#include <iostream>
#include <unordered_map>
#define ERROR_MSG "input file is incorrect"




User::User (std::string &name, rank_map& rank_movie ,shard_rec_ptr
&shard_rec):name_user(name),movie_rank(rank_movie),
rec_ptr_system(shard_rec)
{
}
const std::string &User::get_name() const
{
  return name_user;
}



const rank_map& User::get_ranks () const
{
  return movie_rank;
}





/**
   * function for adding a movie to the DB
   * @param name name of movie
   * @param year year it was made
   * @param features a vector of the movie's features
   * @param rate the user rate for this movie
   */
void User::add_movie_to_rs (const std::string &name, int year,
                            const std::vector<double> &features, double rate)
{
  sp_movie new_m =  rec_ptr_system -> add_movie (name, year,features);
  movie_rank[new_m] = rate;
}

sp_movie User::get_recommendation_by_content () const
{
  return rec_ptr_system->recommend_by_content (*this);
}



sp_movie User::get_recommendation_by_cf (int k) const
{return rec_ptr_system->recommend_by_cf (*this,k);}



double User::get_prediction_score_for_movie (const std::string &name,
                                             int year, int k) const
{
  sp_movie movie = rec_ptr_system->get_movie (name,year);
  return rec_ptr_system->predict_movie_score (*this,movie,k);
}


std::ostream& operator<<(std::ostream& os, const User& rhs)
{
  os<< "name: ";
  os<<rhs.name_user ;
  os<< std::endl;
  os<< *(rhs.rec_ptr_system);
  return os;
}


// implement your cpp code here
