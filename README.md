# Data Oriented Design (trait-based programming)

A simple, data-oriented design system with polymorphism, implemented in C. This system uses a [vtable](https://en.wikipedia.org/wiki/Virtual_method_table)-based approach to achieve polymorphism, allowing for efficient and flexible entity management. This system is the C implementation of [Rust's trait approach](https://doc.rust-lang.org/book/ch10-02-traits.html).

In the future, this system will be used in [Floral](https://github.com/ImSumire/Floral) to offer a flexible, intuitive and high-performance method for polymorphism. And I think this approach fits in well with C's goals for memory management and branch-lessness.

## Why using V-Tables ?
- **Optimization**: It's by far the most efficient polymorphism system because it allows for direct function calls without the need for dynamic dispatch or virtual function tables (so, branchless). This reduces the overhead of function calls and makes the code more predictable. Here, all constant instances are managed in compile-time instead of run-time.
- **Code clarity**: The use of a separate Trait struct to define the methods that can be called on an instance makes the code more modular and easier to understand. It also allows for a clear separation of concerns between the entity's data and its behavior.
- **Flexibility**: It's easy to add new entity types without modifying the existing code. Simply define a new Trait struct and create a new vtable for the new instance type.
