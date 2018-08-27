/** Dynamic arrays.

    The [DynArray] module provides arrays that automatically change their size
    as necessary.  The resizing behavior of dynamic arrays can be adapted
    through customized resizer functions, as described below.

    The interface of this module is similar to the interface of the [Array]
    module in the OCaml standard library, but some functions ({!append}, for
    example) have been changed to modify their argument in-place instead of
    returning a new copy. */;

/** The type of resizable arrays with elements of type ['a]. */
type t('a);

/** Returns the length of an array. */
let length: t('a) => int;

/** [get a i] returns the element with index [i] of [a].  The first element
    has index 0.

    @raise Invalid_argument if [i] is not a valid index of [a]. */
let get: (t('a), int) => 'a;

/** [set a i x] replaces the element with index [i] of [a] by the value [x].
    This function {e cannot} be used to extend an array.

    @raise Invalid_argument if [i] is not a valid index of [a]. */
let set: (t('a), int, 'a) => unit;

/** {2 Array construction} */;

/** [make n x] returns a new dynamic array of length [n] that is initialized
    with [n] copies of [x].

    @raise Invalid_argument if [n] < 0 or if [n] > [Sys.max_array_length]. */
let make: (int, 'a) => t('a);

/** [init n f] returns a new dynamic array of length [n] where the element
    with index [i] is equal to [f i].

    @raise Invalid_argument if [n] < 0 or if [n] > [Sys.max_array_length]. */
let init: (int, int => 'a) => t('a);

/** [sub a i n] returns a new dynamic array containing the elements with
    indices [i], ..., [i + n - 1] of [a].

    @raise Invalid_argument if [i] and [n] do not specify a valid subarray of
    [a]. */
let sub: (t('a), int, int) => t('a);

/** [copy a] returns a new dynamic array containing the same elements as
    [a]. */
let copy: t('a) => t('a);

/** {2 Array modification with automatic resizing} */;

/** [add a x] adds [x] to the end of [a].  The array is automatically
    resized. */
let add: (t('a), 'a) => unit;

/** [insert a x i] inserts [x] into the array [a] at index [i].  The array is
    automatically resized.

    @raise Invalid_argument if [i] is not a valid insertion index of [a].
    Valid insertion indices are [0 .. length a]. */
let insert: (t('a), int, 'a) => unit;

/** [insert_range a1 i1 a2 i2 n] inserts the subarray [sub a2 i2 n] into the
    array [a1] at index [i1].  The array [a1] is automatically resized.

    @raise Invalid_argument if [i1] and [n] do not specify a valid subarray of
    [a1] or if [i2] is not a valid insertion index of [a2]. */
let insert_range: (t('a), int, t('a), int, int) => unit;

/** [remove a i] removes the element with index [i] from [a].  The array is
    automatically resized.

    @raise Invalid_argument if [i] and [n] do not specify a valid subarray of
    [a]. */
let remove: (t('a), int) => unit;

/** [remove_last a] removes the element with index [length a - 1] from [a].
    The array is automatically resized. */
let remove_last: t('a) => unit;

/** [remove_range a i n] removes the elements with indices [i], ..., [i + n -
    1] from [a].  The array is automatically resized.

    @raise Invalid_argument if [i] and [n] do not specify a valid subarray of
    [a]. */
let remove_range: (t('a), int, int) => unit;

/** [remove_all a] removes all elements from [a].  The array is automatically
    resized. */
let remove_all: t('a) => unit;

/** [clear a] removes all elements from [a].  The array is automatically
    resized (same as [remove_all]). */
let clear: t('a) => unit;

/** [append a b] appends the elements of [a] to the end of [b].  The array
    [b] is automatically resized.  */
let append: (t('a), t('a)) => unit;

/** {2 Array modification without automatic resizing} */;

/** [fill a i n x] replaces the elements of the array [a] with indices [i],
    ..., [i + n - 1] by [n] copies of the value [x].  This function {e cannot}
    be used to extend an array.

    @raise Invalid_argument if [i] and [n] do not specify a valid subarray of
    [a]. */
let fill: (t('a), int, int, 'a) => unit;

/** [blit a i b j n] replaces [n] elements of array [b] starting at index [j]
    by [n] elements of array [a] starting at index [i].

    @raise Invalid_argument if [i] and [n] do not specify a valid subarray of
    [a] or [j] and [n] do not specify a valid subarray of [b]. */
let blit: (t('a), int, t('a), int, int) => unit;

/** {2 Iterators} */;

/** [iter f a] applies the function [f] successively to all elements of [a].
    It is equal to [f a1; ..., f an)], where [a1], ..., [an] are the elements
    of the array [a]. */
let iter: ('a => unit, t('a)) => unit;

/** [rev_iter f a] applies the function [f] successively to all elements of
    [a] in reverse direction.  It is equal to [f an; ..., f a1)], where [a1],
    ..., [an] are the elements of the array [a]. */
let rev_iter: ('a => unit, t('a)) => unit;

/** [iteri f a] applies the function [f] successively to all elements of [a]
    and their indices.  It is equal to [f 0 a1; ..., f (n - 1) an)], where
    [a1], ..., [an] are the elements of the array [a]. */
let iteri: ((int, 'a) => unit, t('a)) => unit;

/** [rev_iteri f a] applies the function [f] successively to all elements of
    [a] in reverse direction and their indices.  It is equal to [f (n - 1) an;
    ..., f 0 a1)], where [a1], ..., [an] are the elements of the array [a]. */
let rev_iteri: ((int, 'a) => unit, t('a)) => unit;

/** [fold_left f x a] returns [f (... (f (f x a1) a2) ...) an], where [a1],
    ..., [an] are the elements of [a]. */
let fold_left: (('a, 'b) => 'a, 'a, t('b)) => 'a;

/** [fold_right f a x] returns [f a1 (f a2 (... (f an x) ...))], where [a1],
    ..., [an] are the elements of [a]. */
let fold_right: (('a, 'b) => 'b, t('a), 'b) => 'b;

/** [fold_left2 f x a b] returns [f ( ... (f (f x a1 b1) a2 b2) ... ) an bn],
    where [a1], ..., [an] are the elements of [a], and [b1], ..., [bn] are the
    elements of [b].

    @raise Invalid_argument if the two arrays have different lengths. */
let fold_left2: (('a, 'b, 'c) => 'a, 'a, t('b), t('c)) => 'a;

/** [fold_right2 f a b x] returns [f a1 b1 (f a2 b2 ( ... (f an bn x) ... ))],
    where [a1], ..., [an] are the elements of [a], and [b1], ..., [bn] are the
    elements of [b].

    @raise Invalid_argument if the two arrays have different lengths. */
let fold_right2: (('a, 'b, 'c) => 'c, t('a), t('b), 'c) => 'c;

/** [map f a] returns an array with elements [f a1], ..., [f an], where [a1],
    ..., [an] are the elements of [a]. */
let map: ('a => 'b, t('a)) => t('b);

/** [mapi f a] returns an array with elements [f 0 a1], ..., [f (n - 1) an],
    where [a1], ..., [an] are the elements of [a]. */
let mapi: ((int, 'a) => 'b, t('a)) => t('b);

/** {2 Scanning} */;

/** Tests whether an array is empty. */
let is_empty: t('a) => bool;

/** [for_all p a] returns [true] if [p x = true] for all elements [x] of the
    array [a], and [false] otherwise. */
let for_all: ('a => bool, t('a)) => bool;

/** [exists p a] returns [true] if [p x = true] for some element [x] of the
    array [a], and [false] otherwise. */
let exists: ('a => bool, t('a)) => bool;

/** [for_all2 p a b] returns [true] if [p x y = true] for all pairs of
    elements [x] and [y] where [x] has the same index in [a] as [y] in [b].

    @raise Invalid_argument if [a] and [b] have different lengths. */
let for_all2: (('a, 'b) => bool, t('a), t('b)) => bool;

/** [exists2 p a b] returns [true] if [p x y = true] for some pair of elements
    [x] and [y] where [x] has the same index in [a] as [y] in [b].

    @raise Invalid_argument if [a] and [b] have different lengths. */
let exists2: (('a, 'b) => bool, t('a), t('b)) => bool;

/** {2 Searching} */;

/** [first a] returns [Some x] if [x] is the first element (the element with
    index 0) of [a], or [None] if the array is empty. */
let first: t('a) => option('a);

/** [last a] returns [Some x] if [x] is the last element (the element with
    index [length a - 1]) of [a], or [None] if the array is empty. */
let last: t('a) => option('a);

/** {2 Conversion} */;

/** [to_list a] returns a list containing the elements of [a]. */
/* let to_list: t('a) => list('a); */

/** [of_list l] returns a dynamic array containing the elements of [l]. */
let of_list: list('a) => t('a);

/** [to_array a] returns a new standard OCaml array containing the same
    elements as [a]. */
let to_array: t('a) => array('a);

/** [of_array a] returns a new dynamic array containing the same elements as
    [a]. */
let of_array: array('a) => t('a);

/** {2 Resizer functions}

    A resizer is a function that computes how much space is to be reserved
    when elements are added to or removed from a dynamic array.  When a
    dynamic array is created, a default resizer is assigned to it, which can
    then be changed.  When a dynamic array is copied using the functions
    [sub], [copy], or [map], the new array uses the same resizer as the
    original array.

    A resizer is called with three arguments: the current reserved size of the
    array, the number of elements of the array before the modification, and
    the number of elements of the array after the modification. */;

/** The type of resizer functions. */
type resizer = (~curr_size: int, ~old_length: int, ~new_length: int) => int;

/** A resizer that grows and shrinks an array by doubling or halving the size
    of the array as necessary. */
let doubling_resizer_with_shrinking: resizer;

/** A resizer that grows an array by doubling the size of the array as
    necessary.  It never shrinks the array, which is not a problem in many use
    cases.  This is currently the default resizer. */
let doubling_resizer_without_shrinking: resizer;

/** Sets the resizer function of an array. */
let set_resizer: (t('a), resizer) => unit;

/** Sets the default resizer function.  */
let set_default_resizer: resizer => unit;

/**/

let unsafe_get: (t('a), int) => 'a;

let unsafe_set: (t('a), int, 'a) => unit;