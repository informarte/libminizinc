%-----------------------------------------------------------------------------%
% Requires that the array 'x' is in strict increasing order
%-----------------------------------------------------------------------------%

predicate strictly_increasing(array[int] of var bool: x) =
    analyse_alldifferent(x) /\
    fzn_strictly_increasing_bool(x);

predicate strictly_increasing(array[int] of var int: x) =
    analyse_alldifferent(x) /\
    fzn_strictly_increasing_int(x);

include "fzn_strictly_increasing.mzn";
include "analyse_alldifferent.mzn";