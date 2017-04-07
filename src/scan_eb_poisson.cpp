#include <cmath>
#include "probability_functions.h"

//' Calculate the EB Poisson loglihood ratio statistic for all clusters.
//'
//' Calculate the expectation-based Poisson loglihood ratio statistic for each 
//' zone and duration. The estimate of the relative risk is also calculated and 
//' returned.
//' @param counts A matrix of non-negative integers; the observed counts. Rows
//'    indicate time, ordered from most recent (row 1) to least recent. Columns
//'    indicate locations; the locations are numbered from 1 and up.
//' @param agg_baselines A matrix of positive scalars; the expected values of 
//'    the counts, cumulatively summed over locations (columns). Of the same 
//'    dimensions as \code{counts}.
//' @param zones An integer vector containing the zones, stored one after
//'    another. Each zone is found using the elements of the parameter
//'    \code{zone_lengths}. For example, if the first element of
//'    \code{zone_lengths} is 5, then the first 5 elements of \code{zones}
//'    make up the first zone. If the second element of \code{zone_lengths} is
//'    2, then elements 6 and 7 of \code{zones} make up the second zone, and so
//'    on. Note that the zones are numbered from 0 and up in the input, but
//'    from 1 and up in the output.
//' @param zone_lengths An integer vector holding the number of locations in
//'    each zone.
//' @return A data frame with five columns:
//'    \describe{
//'      \item{zone}{The (number of the) zone.}
//'      \item{duration}{The duration.}
//'      \item{score}{The value of the loglihood ratio statistic.}
//'      \item{relrisk}{The estimated relative risk.}
//'    }
//' @keywords internal
// [[Rcpp::export]]
Rcpp::DataFrame scan_eb_poisson_cpp(const arma::umat& counts,
                                    const arma::mat&  agg_baselines,
                                    const arma::uvec& zones,
                                    const arma::uvec& zone_lengths) {
  int max_duration = counts.n_rows;
  int n_zones = zone_lengths.n_elem;
  
  // Cumulative sums of counts over locations (columns)
  arma::umat agg_counts = arma::cumsum(counts, 0);

  // Components of returned list
  arma::uvec zone_numbers (n_zones * max_duration);
  arma::uvec durations    (n_zones * max_duration);
  arma::vec  scores       (n_zones * max_duration);
  arma::vec  relrisks     (n_zones * max_duration);

  int i = 0; // Storage index

  for (int d = 0; d < max_duration; ++d) {

    // Indices for extracting the current zone
    int zone_start = 0;
    int zone_end = 0;
    
    // Index for the current row
    arma::uvec row_idx (1);
    row_idx[0] = d;

    for (int z = 0; z < n_zones; ++z) {
      // Extract zone
      zone_end = zone_start + zone_lengths[z] - 1;
      arma::uvec current_zone = zones(arma::span(zone_start, zone_end));
      
      // Calculate count and baseline for zone
      double C = arma::accu(agg_counts.submat(row_idx, current_zone));
      double B = arma::accu(agg_baselines.submat(row_idx, current_zone));

      // Store results
      scores[i]       = (C > B ? C * (log(C) - log(B)) + B - C : 0.0);
      relrisks[i]     = std::max(1.0, C / B);
      zone_numbers[i] = z + 1;
      durations[i]    = d + 1;

      // Update indices
      zone_start = zone_end + 1;
      ++i;
    }
  }
  return Rcpp::DataFrame::create(Rcpp::Named("zone")     = zone_numbers,
                                 Rcpp::Named("duration") = durations,
                                 Rcpp::Named("score")    = scores,
                                 Rcpp::Named("relrisk")  = relrisks);
}

//' Calculate the highest-value EB Poisson loglihood ratio statistic.
//'
//' Calculate the expectation-based Poisson loglihood ratio statistic for each 
//' zone and duration, but only keep the zone and duration with the highest 
//' value (the MLC). The estimate of the relative risks inside and outside the 
//' MLC is also calculated and returned.
//' @param counts A matrix of non-negative integers; the observed counts. Rows
//'    indicate time, ordered from most recent (row 1) to least recent. Columns
//'    indicate locations; the locations are numbered from 1 and up.
//' @param agg_baselines A matrix of positive scalars; the expected values of 
//'    the counts, cumulatively summed over locations (columns). Of the same 
//'    dimensions as \code{counts}.
//' @param zones An integer vector containing the zones, stored one after
//'    another. Each zone is found using the elements of the parameter
//'    \code{zone_lengths}. For example, if the first element of
//'    \code{zone_lengths} is 5, then the first 5 elements of \code{zones}
//'    make up the first zone. If the second element of \code{zone_lengths} is
//'    2, then elements 6 and 7 of \code{zones} make up the second zone, and so
//'    on. Note that the zones are numbered from 0 and up in the input, but
//'    from 1 and up in the output.
//' @param zone_lengths An integer vector holding the number of locations in
//'    each zone.
//' @return A data frame with five columns:
//'    \describe{
//'      \item{zone}{The top-scoring zone (spatial component of MLC).}
//'      \item{duration}{The corresponding duration (time-length of MLC).}
//'      \item{score}{The value of the loglihood ratio statistic (the scan
//'                   statistic).}
//'      \item{relrisk}{The estimated relative risk.}
//'    }
//' @keywords internal
// [[Rcpp::export]]
Rcpp::DataFrame scan_eb_poisson_cpp_max(const arma::umat& counts,
                                        const arma::mat&  agg_baselines,
                                        const arma::uvec& zones,
                                        const arma::uvec& zone_lengths) {
  int max_duration = counts.n_rows;
  int n_zones = zone_lengths.n_elem;
  
  // Cumulative sums of counts over locations (columns)
  arma::umat agg_counts = arma::cumsum(counts, 0);
  
  // Return values
  int    mlc_zone     = -1;
  int    mlc_duration = -1;
  double mlc_score    = -1.0;
  double mlc_relrisk  = -1.0;
  
  for (int d = 0; d < max_duration; ++d) {
    
    // Indices for extracting the current zone
    int zone_start = 0;
    int zone_end = 0;
    
    // Index for the current row
    arma::uvec row_idx (1);
    row_idx[0] = d;
    
    for (int z = 0; z < n_zones; ++z) {
      // Extract zone
      zone_end = zone_start + zone_lengths[z] - 1;
      arma::uvec current_zone = zones(arma::span(zone_start, zone_end));
      
      // Calculate count and baseline for zone
      double C = arma::accu(agg_counts.submat(row_idx, current_zone));
      double B = arma::accu(agg_baselines.submat(row_idx, current_zone));
      
      double score = (C > B ? C * (log(C) - log(B)) + B - C : 0.0);
      
      // Update return values if new score is highest so far
      if (score > mlc_score) {
        mlc_zone       = z + 1;
        mlc_duration   = d + 1;
        mlc_score      = score;
        mlc_relrisk    = std::max(1.0, C / B);
      }
      
      zone_start = zone_end + 1;
    }
  }
  return Rcpp::DataFrame::create(Rcpp::Named("zone")     = mlc_zone,
                                 Rcpp::Named("duration") = mlc_duration,
                                 Rcpp::Named("score")    = mlc_score,
                                 Rcpp::Named("relrisk")  = mlc_relrisk);
}

