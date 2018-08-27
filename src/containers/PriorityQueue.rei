/** Priority queues.

The [PriorityQueue] module provides a polymorphic and a functorial
interface to an imperative priority queue data structure.  A queue is
implemented by embeddeding a heap in a resizable array.

The polymorphic interface requires that the elements in a priority queue
are distinct w.r.t. [(=)].  The functorial interface requires that the
elements in a priority queue are distinct w.r.t. the [equal] function in
their [HashedType] module.  Otherwise the functions based on element
values ([mem], [remove], [reorder_up], and [reorder_down]) may not work
correctly. */;

/** The type of priority orders on ['a].  A priority order [ord] is a
non-strict total order where [ord a b = true] means that the priority of
[b] is not higher than the priority of [a].  When the priority of an
element changes, the queue must be notified using the [reorder_up] or
[reorder_down] function. */
type order('a) = ('a, 'a) => bool;

/** The type of priority queues with element type ['a]. */
type t('a);

/** [make ord] creates a new priority queue with order [ord]. */
let make: order('a) => t('a);

/** Returns the number of elements in a queue. */
let length: t('a) => int;

/** Tests whether a queue is empty. */
let is_empty: t('a) => bool;

/** Adds an elements to the queue. */
let add: (t('a), 'a) => unit;

/** Tests whether a queue contains a given element. */
let mem: (t('a), 'a) => bool;

/** [first q] returns an element with maximal priority contained in the queue
    [q].

    @raise Failure if [q] is empty. */
let first: t('a) => 'a;

/** [remove_first q] removes the element returned by [first q] from the queue
    [q].

    @raise Failure if [q] is empty. */
let remove_first: t('a) => unit;

/** [remove q x] removes the element [x] from the queue [q].  If [q] does not
    contain the element [x], the function does nothing. */
let remove: (t('a), 'a) => unit;

/** Removes all elements from a queue. */
let clear: t('a) => unit;

/** [reorder_up q x] notifies the queue [q] that the priority of the element
    [x] has increased.  If [q] does not contain [x], the function does
    nothing. */
let reorder_up: (t('a), 'a) => unit;

/** [reorder_down q x] notifies the queue [q] that the priority of the element
    [x] has decreased.  If [q] does not contain [x], the function does
    nothing. */
let reorder_down: (t('a), 'a) => unit;

/** Input signature of the functor {!PriorityQueue.Make}. */
module type HashedType = {
  /** The element type. */
  type t;
  /** The equality predicate on the element type. */
  let equal: (t, t) => bool;
  /** A hash function on the elements.  This function must be compatible with
      equality, which means that if [equal x y = true], then [hash] must
      compute the same hash values for [x] and [y]. */
  let hash: t => int;
};

/** Output signature of the functor {!PriorityQueue.Make}. */
module type S = {
  /** The element type. */
  type elt;
  /** The type of priority orders on [elt].  A priority order [ord] is a
      non-strict total order where [ord a b = true] means that the priority of
      [b] is not higher than the priority of [a].  When the priority of an
      element changes, the queue must be notified using the [reorder_up] or
      [reorder_down] function. */
  type order = (elt, elt) => bool;
  /** The type of priority queues with element type [elt]. */
  type t;
  /** [make ord] creates a new priority queue with order [ord]. */
  let make: order => t;
  /** Returns the number of elements in a queue. */
  let length: t => int;
  /** Tests whether a queue is empty. */
  let is_empty: t => bool;
  /** Adds an elements to the queue. */
  let add: (t, elt) => unit;
  /** Tests whether a queue contains a given element. */
  let mem: (t, elt) => bool;
  /** [first q] returns an element with maximal priority contained in the
      queue [q].

      @raise Failure if [q] is empty. */
  let first: t => elt;
  /** [remove_first q] removes the element returned by [first q] from the
      queue [q].

      @raise Failure if [q] is empty. */
  let remove_first: t => unit;
  /** [remove q x] removes the element [x] from the queue [q].  If [q] does
      not contain the element [x], the function does nothing. */
  let remove: (t, elt) => unit;
  /** Removes all elements from a queue. */
  let clear: t => unit;
  /** [reorder_up q x] notifies the queue [q] that the priority of the element
      [x] has increased.  If [q] does not contain [x], the function does
      nothing. */
  let reorder_up: (t, elt) => unit;
  /** [reorder_down q x] notifies the queue [q] that the priority of the
      element [x] has decreased.  If [q] does not contain [x], the function does
      nothing. */
  let reorder_down: (t, elt) => unit;
};

module Make: (H: HashedType) => S with type elt = H.t;

/**/;

let is_heap: t('a) => bool;