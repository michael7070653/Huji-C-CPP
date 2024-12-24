#include "Movie.h"
#include "User.h"
#include "RecommendationSystem.h"
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>
#include "numeric"
#define ERROR_MSG "input file is incorrect"
#define MAX_RANK 10
#define MIN_RANK 1



using std::map;
using std::vector;
using std::pair;
using std::sort;



bool compare_movie(const sp_movie& l, const sp_movie &r)
{
  return (*l)<(*r);
}


bool compere_pairs(pair<sp_movie ,double>& p_1 , pair<sp_movie ,double>& p_2)
{
  return p_1.second>p_2.second;
}

RecommendationSystem::RecommendationSystem ():
arr_(compare_movie)
{
}



/**
 * a function that calculates the movie with
 * highest score based on movie features
 * @param ranks user ranking to use for algorithm
 * @return shared pointer to movie in system
 */
sp_movie RecommendationSystem::recommend_by_content (const User &user)
{
  double average = get_average (user);
  vector<double> pref_vec = get_vector_prefernce
      (average,user.get_ranks());
  sp_movie best = nullptr;
  double max = 0;
  for(const auto &item: arr_)
  {
    const auto & check_in_rank =
        user.get_ranks().find (item.first);
    if(check_in_rank == user.get_ranks().end())
    {
      vector<double> c = arr_[item.first];
      double temp = get_inner_products (pref_vec,c);
      if (max == 0)
      {
        max = temp;
        best = item.first;
      }
      if(temp > max )
      {
        max = temp;
        best = item.first;
      }
    }
  }
  return best;
}



/**
 * a function that calculates the movie with highest
 * predicted score based on ranking of other movies
 * @param ranks user ranking to use for algorithm
 * @param k
 * @return shared pointer to movie in system
 */

sp_movie RecommendationSystem::recommend_by_cf (const User &user, int k)
{
  vector<pair<sp_movie ,double>> imag_vector;
  for (const auto & movie: arr_)
  {
    const auto & check_in_rank =
        user.get_ranks().find (movie.first);
    if(check_in_rank == user.get_ranks().end())
    {
      double res = predict_movie_score (user,movie.first,k);
      imag_vector.emplace_back (movie.first,res);
    }
  }
  sort (imag_vector.begin(),imag_vector.end(), compere_pairs);
  return imag_vector[0].first;
}

/**
  * adds a new movie to the system
  * @param name name of movie
  * @param year year it was made
  * @param features features for movie
  * @return shared pointer for movie in system
  */
sp_movie RecommendationSystem::add_movie (const std::string &name,int year,
             const std::vector<double> &features)
{
  for(const auto & x: features)
  {
    if (x <MIN_RANK || x> MAX_RANK)
    {throw std::invalid_argument (ERROR_MSG);}
  }
  sp_movie new_movie = std::make_shared<Movie>(name,year);
  arr_[new_movie] = features;
  return new_movie;
}




/**
 * gets a shared pointer to movie in system
 * @param name name of movie
 * @param year year movie was made
 * @return shared pointer to movie in system
 */

sp_movie RecommendationSystem::
get_movie (const std::string &name, int year) const
{
  sp_movie check = std::make_shared<Movie>(name,year);
  if (arr_.find (check) != arr_.end())
  {
    return arr_.find (check)->first;
  }
  return nullptr;
}





/**
 * Predicts the movie score for a given user and movie
 * @param user User for whom to predict the movie score
 * @param movie Movie for which to predict the score
 * @param k Number of top movies to consider in the prediction
 * @return Predicted movie score
 */

double RecommendationSystem ::predict_movie_score
(const User &user, const sp_movie &movie, int k)
{
  const rank_map& user_rank = user.get_ranks();
  double up = 0;
  vector<pair<sp_movie ,double>> imag_vector;
  for(const auto &item:user.get_ranks())
  {
    double res = get_inner_products (arr_[movie],arr_[item.first]);
    imag_vector.emplace_back(item.first,res);
  }
  sort (imag_vector.begin(), imag_vector.end(), compere_pairs );
  for(int i = 0; i < k ;i++)
  {
      double rank_movie = user_rank.at(imag_vector[i].first);
      up += imag_vector[i].second * rank_movie;
  }
  double res_end = get_imagine_sum_for_k(k,imag_vector);
  return up/res_end;
}







std::ostream &operator<< (std::ostream &os, RecommendationSystem &rhs){
  for(const auto &item:rhs.arr_)
  {
    os<<*(item.first);
  }
  return os;
}


//private func




/**
 * Gets the average rank for a user
 * @param user User for whom to calculate the average rank
 * @return Average rank for the user
 */

double RecommendationSystem::get_average (const User&user)
{
  double sum = 0;
  int num = 0;
  for(const auto &item:user.get_ranks()){
    sum+= item.second;
    num++;
  }
  return  sum/num;
}




/**
 * Gets a vector of preferences based on user rank and average rank
 * @param average Average rank for the user
 * @param rank Rank map for the user
 * @return Vector of preferences
 */

vector<double> RecommendationSystem::
get_vector_prefernce (double average,const rank_map &rank)
{
  size_t size = arr_.begin()->second.size();
  vector<double> new_ref(size,0);

  for(size_t i = 0; i < size ; i++)
  {
    for(const auto &item:rank)
    {
      vector<double> pref = arr_[item.first];
        double x = item.second - average;
        new_ref[i] += x * pref[i];
    }
  }
  return new_ref;

}





/**
 * Calculates the inner product between two vectors
 * @param pref User preferences vector
 * @param characteristics Movie characteristics vector
 * @return Inner product between the vectors
 */

double RecommendationSystem::
 get_inner_products (const vector<double> &pref,vector<double>
     &characteristics)
{
  double up = std::inner_product(pref.begin(),pref.end(),characteristics.begin(),0.0);

  double norm_c = std::inner_product
      (characteristics.begin(),characteristics.end(),
                                      characteristics
      .begin(),0.0);


  double norm_pref = std::inner_product (pref.begin(),pref.end(),pref
      .begin(),0.0);

  return up/(sqrt (norm_pref)* sqrt (norm_c));
}



/**
 * Calculates the sum of the top k values in a vector of pairs
 * @param k Number of top values to consider
 * @param vec Vector of pairs where the second element is used for the sum
 * @return Sum of the top k values
 */

double RecommendationSystem::get_imagine_sum_for_k
(int k, vector<pair<sp_movie, double>>& vec)
{
  double res = 0;
  for(int i = 0;i < k ;i++)
  {
    res += vec[i].second;
  }
  return res;
}

