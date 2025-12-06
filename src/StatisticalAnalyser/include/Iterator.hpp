#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <Eigen/Dense>
namespace SCT {
namespace StatisticalAnalyses {

class RowIterator {
public:
  RowIterator(const Eigen::MatrixXd *mat, int idx) : mat_(mat), idx_(idx) {}

  Eigen::MatrixXd::ConstRowXpr operator*() const { return mat_->row(idx_); }

  RowIterator &operator++() {
    idx_++;
    return *this;
  }

  bool operator!=(const RowIterator &other) const { return idx_ != other.idx_; }

private:
  const Eigen::MatrixXd *mat_;
  int idx_;
};

class ColIterator {
public:
  ColIterator(const Eigen::MatrixXd *mat, int idx) : mat_(mat), idx_(idx) {}

  Eigen::MatrixXd::ConstColXpr operator*() const { return mat_->col(idx_); }

  ColIterator &operator++() {
    idx_++;
    return *this;
  }

  bool operator!=(const ColIterator &other) const { return idx_ != other.idx_; }

private:
  const Eigen::MatrixXd *mat_;
  int idx_;
};

struct RowView {
  const Eigen::MatrixXd &mat;
  RowView(const Eigen::MatrixXd &m) : mat(m) {}
  RowIterator begin() const { return RowIterator(&mat, 0); }
  RowIterator end() const { return RowIterator(&mat, mat.rows()); }
};

struct ColView {
  const Eigen::MatrixXd &mat;
  ColView(const Eigen::MatrixXd &m) : mat(m) {}
  ColIterator begin() const { return ColIterator(&mat, 0); }
  ColIterator end() const { return ColIterator(&mat, mat.cols()); }
};
} // namespace StatisticalAnalyses
} // namespace SCT
#endif