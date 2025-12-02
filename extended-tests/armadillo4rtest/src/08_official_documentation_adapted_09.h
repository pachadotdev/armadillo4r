[[cpp4r::register]] integers sub2ind1_(const int& n) {
  mat M(n, n, fill::randu);

  uword i = sub2ind(size(M), n - 1, n - 1);

  return integers({static_cast<int>(i)});
}

[[cpp4r::register]] doubles_matrix<> symmatu1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = symmatu(A);
  return as_doubles_matrix(B);
}

[[cpp4r::register]] doubles trace1_(const int& n) {
  mat A(n, n, fill::randu);
  return doubles({trace(A)});
}

[[cpp4r::register]] list trans1_(const int& n) {
  mat A(n, n, fill::randu);

  mat B = trans(A);
  mat C = A.t();  // same as trans(A)

  writable::list res(2);

  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(C);

  return res;
}

[[cpp4r::register]] doubles_matrix<> trapz1_(const int& n) {
  vec X = linspace<vec>(0, datum::pi, n);
  vec Y = sin(X);

  mat Z = trapz(X, Y);

  return as_doubles_matrix(Z);
}

[[cpp4r::register]] doubles_matrix<> trimatu1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = trimatu(A);
  return as_doubles_matrix(B);
}

[[cpp4r::register]] integers trimatu_ind1_(const int& n) {
  mat A(n, n, fill::randu);
  uvec B = trimatu_ind(size(A));
  return as_integers(B);
}

[[cpp4r::register]] doubles unique1_(const int& n) {
  mat A(n, n, fill::randu);
  A(0, 0) = A(1, 1);
  vec B = unique(A);
  return as_doubles(B);
}

[[cpp4r::register]] list vecnorm1_(const int& n) {
  mat A(n, n, fill::randu);

  colvec a = vecnorm(A, 2).t();
  colvec b = vecnorm(A, "inf", 1);

  writable::list res(2);
  res[0] = as_doubles(a);
  res[1] = as_doubles(b);

  return res;
}

[[cpp4r::register]] doubles vectorise1_(const int& n) {
  mat A(n, n, fill::randu);
  vec B = vectorise(A);
  return as_doubles(B);
}

[[cpp4r::register]] list misc1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = exp(A);
  mat C = log(A);
  mat D = sqrt(A);
  mat E = round(A);
  mat F = sign(A);

  writable::list res(6);
  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);
  res[2] = as_doubles_matrix(C);
  res[3] = as_doubles_matrix(D);
  res[4] = as_doubles_matrix(E);
  res[5] = as_doubles_matrix(F);

  return res;
}

[[cpp4r::register]] list trig1_(const int& n) {
  mat A(n, n, fill::randu);
  mat B = cos(A);
  mat C = sin(A);
  mat D = tan(A);
  mat E = atan2(C, B);
  mat F = hypot(B, C);

  writable::list res(6);
  res[0] = as_doubles_matrix(A);
  res[1] = as_doubles_matrix(B);
  res[2] = as_doubles_matrix(C);
  res[3] = as_doubles_matrix(D);
  res[4] = as_doubles_matrix(E);
  res[5] = as_doubles_matrix(F);

  return res;
}

[[cpp4r::register]] list mean1_(const doubles_matrix<>& X, const doubles_matrix<>& Y) {
  mat A = as_Mat(X);
  mat B = as_Mat(Y);

  // create a cube with 3 copies of B + random noise
  cube C(B.n_rows, B.n_cols, 3);
  C.slice(0) = B + 0.1 * randn<mat>(B.n_rows, B.n_cols);
  C.slice(1) = B + 0.2 * randn<mat>(B.n_rows, B.n_cols);
  C.slice(2) = B + 0.3 * randn<mat>(B.n_rows, B.n_cols);

  vec D = mean(A).t();
  vec E = mean(A, 1);
  vec F = mean(mean(B, 1), 1);

  writable::list res(3);
  res[0] = as_doubles(D);
  res[1] = as_doubles(E);
  res[2] = as_doubles(F);

  return res;
}

[[cpp4r::register]] list median1_(const doubles_matrix<>& X, const doubles_matrix<>& Y) {
  mat A = as_Mat(X);
  mat B = as_Mat(Y);

  vec C = median(A).t();
  vec D = median(A, 1);
  vec E = median(median(B, 1), 1);

  writable::list res(3);
  res[0] = as_doubles(C);
  res[1] = as_doubles(D);
  res[2] = as_doubles(E);

  return res;
}

[[cpp4r::register]] list stddev1_(const doubles_matrix<>& X, const doubles_matrix<>& Y) {
  mat A = as_Mat(X);
  mat B = as_Mat(Y);

  vec C = stddev(A).t();
  vec D = stddev(A, 1).t();
  vec E = stddev(A, 1, 1);

  writable::list res(3);
  res[0] = as_doubles(C);
  res[1] = as_doubles(D);
  res[2] = as_doubles(E);

  return res;
}

[[cpp4r::register]] list var1_(const doubles_matrix<>& X, const doubles_matrix<>& Y) {
  mat A = as_Mat(X);
  mat B = as_Mat(Y);

  vec C = var(A).t();
  vec D = var(A, 1).t();
  vec E = var(A, 1, 1);

  writable::list res(3);
  res[0] = as_doubles(C);
  res[1] = as_doubles(D);
  res[2] = as_doubles(E);

  return res;
}

[[cpp4r::register]] list range1_(const doubles_matrix<>& X, const doubles_matrix<>& Y) {
  mat A = as_Mat(X);
  mat B = as_Mat(Y);

  vec C = range(A).t();
  vec D = range(A, 1);

  writable::list res(2);
  res[0] = as_doubles(C);
  res[1] = as_doubles(D);

  return res;
}

[[cpp4r::register]] list cov1_(const doubles_matrix<>& X, const doubles_matrix<>& Y) {
  mat A = as_Mat(X);
  mat B = as_Mat(Y);

  mat C = cov(A, B);
  mat D = cov(A, B, 1);

  writable::list res(2);
  res[0] = as_doubles_matrix(C);
  res[1] = as_doubles_matrix(D);

  return res;
}

[[cpp4r::register]] list cor1_(const doubles_matrix<>& X, const doubles_matrix<>& Y) {
  mat A = as_Mat(X);
  mat B = as_Mat(Y);

  mat C = cor(A, B);
  mat D = cor(A, B, 1);

  writable::list res(2);
  res[0] = as_doubles_matrix(C);
  res[1] = as_doubles_matrix(D);

  return res;
}

[[cpp4r::register]] list hist1_(const int& n) {
  vec A = randu<vec>(n);

  uvec h1 = hist(A, 11);
  uvec h2 = hist(A, linspace<vec>(-2, 2, 11));

  writable::list res(2);
  res[0] = as_integers(h1);
  res[1] = as_integers(h2);

  return res;
}

[[cpp4r::register]] integers histc1_(const int& n) {
  vec A = randu<vec>(n);

  uvec h = histc(A, linspace<vec>(-2, 2, 11));

  return as_integers(h);
}

[[cpp4r::register]] doubles quantile1_(const int& n) {
  vec A = randu<vec>(n);

  vec P = {0.0, 0.25, 0.50, 0.75, 1.0};
  vec Q = quantile(A, P);

  return as_doubles(Q);
}

[[cpp4r::register]] list normpdf1_(const int& n) {
  vec X = randu<vec>(n);
  vec M = randu<vec>(n);
  vec S = randu<vec>(n);

  vec P1 = normpdf(X);
  vec P2 = normpdf(X, M, S);
  vec P3 = normpdf(1.23, M, S);
  vec P4 = normpdf(X, 4.56, 7.89);
  double P5 = normpdf(1.23, 4.56, 7.89);

  writable::list res(5);

  res[0] = as_doubles(P1);
  res[1] = as_doubles(P2);
  res[2] = as_doubles(P3);
  res[3] = as_doubles(P4);
  res[4] = as_doubles({P5});

  return res;
}

[[cpp4r::register]] list lognormpdf1_(const int& n) {
  vec X = randu<vec>(n);
  vec M = randu<vec>(n);
  vec S = randu<vec>(n);

  vec P1 = log_normpdf(X);
  vec P2 = log_normpdf(X, M, S);
  vec P3 = log_normpdf(1.23, M, S);
  vec P4 = log_normpdf(X, 4.56, 7.89);
  double P5 = log_normpdf(1.23, 4.56, 7.89);

  writable::list res(5);

  res[0] = as_doubles(P1);
  res[1] = as_doubles(P2);
  res[2] = as_doubles(P3);
  res[3] = as_doubles(P4);
  res[4] = as_doubles({P5});

  return res;
}

[[cpp4r::register]] list normcdf1_(const int& n) {
  vec X = randu<vec>(n);
  vec M = randu<vec>(n);
  vec S = randu<vec>(n);

  vec P1 = normcdf(X);
  vec P2 = normcdf(X, M, S);
  vec P3 = normcdf(1.23, M, S);
  vec P4 = normcdf(X, 4.56, 7.89);
  double P5 = normcdf(1.23, 4.56, 7.89);

  writable::list res(5);

  res[0] = as_doubles(P1);
  res[1] = as_doubles(P2);
  res[2] = as_doubles(P3);
  res[3] = as_doubles(P4);
  res[4] = as_doubles({P5});

  return res;
}

[[cpp4r::register]] doubles_matrix<> mvnrnd1_(const int& n, const int& m) {
  vec M = randu<vec>(n);

  mat B = randu<mat>(n, n);
  mat C = B.t() * B;

  mat X = mvnrnd(M, C, m);

  return as_doubles_matrix(X);
}

[[cpp4r::register]] list chi2rnd1_(const int& n, const int& m) {
  mat X = chi2rnd(2, n, m);
  mat Y = randi<mat>(n, m, distr_param(1, 10));
  mat Z = chi2rnd(Y);

  writable::list res(2);
  res[0] = as_doubles_matrix(X);
  res[1] = as_doubles_matrix(Z);

  return res;
}

[[cpp4r::register]] doubles_matrix<> wishrnd1_(const int& n) {
  mat X = randu<mat>(n, n);
  mat S = X.t() * X;

  mat W = wishrnd(S, 6.7);

  return as_doubles_matrix(W);
}

[[cpp4r::register]] doubles_matrix<> iwishrnd1_(const int& n, const double& d) {
  mat X = randu<mat>(n, n);
  mat T = X.t() * X;

  mat W = iwishrnd(T, d);

  return as_doubles_matrix(W);
}

[[cpp4r::register]] list kmeans1_(const int& n, const int& d) {
  mat data(d, n, fill::randu);

  mat means;

  bool status = kmeans(means, data, 2, random_subset, 10, true);

  if (status == false) {
    stop("clustering failed");
  }

  writable::list res(2);

  res[0] = logicals({status});
  res[1] = as_doubles_matrix(means);

  return res;
}

[[cpp4r::register]] list gmm1_(const int& n, const int& d) {
  // create synthetic data with 2 Gaussians

  mat data(d, n, fill::zeros);

  vec mean0 = linspace<vec>(1, d, d);
  vec mean1 = mean0 + 2;

  int i = 0;

  while (i < n) {
    if (i < n) {
      data.col(i) = mean0 + randn<vec>(d);
      ++i;
    }
    if (i < n) {
      data.col(i) = mean0 + randn<vec>(d);
      ++i;
    }
    if (i < n) {
      data.col(i) = mean1 + randn<vec>(d);
      ++i;
    }
  }

  // model the data as a diagonal GMM with 2 Gaussians

  gmm_diag model;

  bool status = model.learn(data, 2, maha_dist, random_subset, 10, 5, 1e-5, true);

  if (status == false) {
    stop("learning failed");
  }

  model.means.print("means:");

  double scalar_likelihood = model.log_p(data.col(0));
  rowvec set_likelihood = model.log_p(data.cols(0, 9));

  double overall_likelihood = model.avg_log_p(data);

  uword gaus_id = model.assign(data.col(0), eucl_dist);
  urowvec gaus_ids = model.assign(data.cols(0, 9), prob_dist);

  rowvec hist1 = model.norm_hist(data, eucl_dist);
  urowvec hist2 = model.raw_hist(data, prob_dist);

  writable::list res(9);

  res[0] = logicals({status});
  res[1] = as_doubles_matrix(model.means);
  res[2] = as_doubles({scalar_likelihood});
  res[3] = as_doubles(set_likelihood.t());
  res[4] = as_doubles({overall_likelihood});
  res[5] = as_integers(gaus_id);
  res[6] = as_integers(gaus_ids.t());
  res[7] = as_doubles(hist1.t());
  res[8] = as_integers(hist2.t());

  return res;
}

[[cpp4r::register]] int saveload1_(const int& n) {
  arma::mat A(n, n, fill::randu);

  // default save format is arma_binary
  A.save("A.bin");

  // save in raw_ascii format
  A.save("A.txt", arma::raw_ascii);

  // save in CSV format without a header
  A.save("A.csv", arma::csv_ascii);

  // save in CSV format with a header
  arma::field<std::string> header(A.n_cols);
  header(0) = "foo";
  header(1) = "bar";  // etc
  A.save(arma::csv_name("A.csv", header));

  // save in HDF5 format with internal dataset named as "my_data"
  // see the caveats
  // A.save(arma::hdf5_name("A.h5", "my_data"));

  // automatically detect format type while loading
  arma::mat B;
  B.load("A.bin");

  // force loading in arma_ascii format
  arma::mat C;
  C.load("A.txt", arma::arma_ascii);

  // example of testing for success
  arma::mat D;
  bool ok = D.load("A.bin");

  if (ok == true) {
    message("Matrix loaded successfully");
  } else {
    stop("Problem with loading");
  }

  return 0;
}

[[cpp4r::register]] int saveload2_(const int& n, const int& m) {
  arma::field<arma::mat> F(m);

  for (int i = 0; i < m; i++) {
    F(i) = arma::mat(n, n, fill::randu);
  }

  // default save format is arma_binary
  F.save("F.bin");

  // save in PPM format
  F.save("F.ppm", arma::ppm_binary);

  // automatically detect format type while loading
  arma::field<arma::mat> G;
  G.load("F.bin");

  return 0;
}

[[cpp4r::register]] list conv1_(const doubles& x, const doubles& y) {
  vec a = as_col(x);
  vec b = as_col(y);

  vec c = conv(a, b);
  vec d = conv(a, b, "same");

  writable::list out(2);
  out[0] = as_doubles(c);
  out[1] = as_doubles(d);

  return out;
}
