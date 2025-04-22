# Load required libraries
# install.packages("tidyverse",repos = "http://cran.us.r-project.org")

# library(dplyr)
library(readr)
# library(stringr)


# Define utility functions

parse_file <- function(file_path) {
    # Read the file content
    file_content <- readLines(file_path, warn = FALSE)

    # Extract objects
    objects_start <- grep("objects", file_content)
    if (length(objects_start) == 0) {
        stop("No 'objects' section found in the file.")
    }
    objects <- strsplit(file_content[objects_start], " ")[[1]]
    objects <- objects[objects != "" & objects != "(:objects"]
    objects <- setdiff(objects, ")") # Remove closing parentheses

    # Extract initial state
    init_start <- grep(":INIT", file_content)
    init_end <- grep(":goal", file_content)
    if (length(init_start) == 0 || length(init_end) == 0) {
        stop("No ':INIT' or ':goal' section found in the file.")
    }
    # Handle multi-line :INIT section
    init_lines <- file_content[(init_start):(init_end - 1)]
    init_lines <- paste(init_lines, collapse = " ") # Combine into one line
    init_lines <- gsub("^\\(:INIT\\s*|\\s*\\)$", "", init_lines) # Remove wrappers
    init_lines <- unlist(strsplit(init_lines, "\\)\\s*")) # Split by ") "
    init_lines <- paste0(init_lines, ")") # Add closing parenthesis back
    filtered_init <- grep("\\(ONTABLE \\w+\\)|\\(ON \\w+ \\w+\\)", init_lines, value = TRUE)

    # Extract goal state
    goal_start <- grep(":goal", file_content)
    goal_line <- file_content[goal_start]
    goal_line <- gsub("^\\(:goal \\(AND |\\)\\)$", "", goal_line) # Remove wrappers
    goal_operations <- unlist(strsplit(goal_line, "\\)\\s*")) # Split by ") "
    goal_operations <- paste0(goal_operations, ")") # Add closing parenthesis back
    filtered_goal <- grep("\\(ON \\w+ \\w+\\)", goal_operations, value = TRUE)

    # Return the parsed components
    return(list(
        objects = objects,
        filtered_init = filtered_init,
        filtered_goal = filtered_goal
    ))
}

parse_config <- function(objects, config_strings) {
    # Initialize the configuration as a list of empty lists
    config <- vector("list", length(objects))
    for (i in seq_along(config)) {
        config[[i]] <- list(-1, -1) # Each block starts clear and on the table
    }

    for (line in config_strings) {
        tokens <- strsplit(gsub("[()]", "", line), " ")[[1]]

        if (tokens[1] == "ONTABLE") {
            # Block is on the table
            index <- match(tokens[2], objects)
            config[[index]][[1]] <- -1 # No block above
            config[[index]][[2]] <- -1 # On the table
        } else if (tokens[1] == "ON") {
            # Block is stacked on another block
            index1 <- match(tokens[2], objects) # Block being moved
            index2 <- match(tokens[3], objects) # Block it's on
            config[[index1]][[2]] <- index2 # Block below
            config[[index2]][[1]] <- index1 # Block above
        }
    }

    return(config)
}

print_config <- function(config, objects, label = "Configuration") {
    # Initialize an empty list to store all stacks
    stacks <- list()

    # Find all blocks on the table
    bottom_blocks <- which(sapply(config, function(x) x[[2]] == -1))

    # Build stacks starting from each bottom block
    for (block in bottom_blocks) {
        stack <- character(0)
        current <- block

        # Traverse upwards to build the stack
        while (current != -1) {
            stack <- c(stack, objects[current])
            current <- config[[current]][[1]] # Move to the block above
        }

        stacks <- append(stacks, list(stack))
    }

    # Sort stacks by the first block's order in `objects`
    stacks <- stacks[order(sapply(stacks, function(stack) match(stack[1], objects)))]

    # Print the stacks in the desired format
    cat(label, ":\n")
    for (stack in stacks) {
        cat(paste(stack, collapse = " | "), "\n")
    }
}

expand_state <- function(state, objects, explored) {
    config <- state$config
    children <- list()

    for (i in seq_along(config)) {
        # Check if the block is clear (no block above it)
        if (config[[i]][[1]] == -1) {
            # Generate a move to the table
            if (config[[i]][[2]] != -1) { # If the block is not already on the table
                new_config <- lapply(config, function(x) list(x[[1]], x[[2]])) # Deep copy of config
                below_block <- config[[i]][[2]]
                new_config[[i]][[2]] <- -1 # Move the block to the table
                new_config[[below_block]][[1]] <- -1 # Clear the block below

                action <- paste0("Move(", objects[i], ",", objects[below_block], ",table)")
                child <- list(
                    config = new_config,
                    parent = state,
                    action = action,
                    cost = state$cost + 1,
                    depth = state$depth + 1 # Increment depth
                )
                children <- append(children, list(child))
            }

            # Generate moves to other blocks
            for (j in seq_along(config)) {
                if (i != j && config[[j]][[1]] == -1) { # Block j must be clear
                    new_config <- lapply(config, function(x) list(x[[1]], x[[2]])) # Deep copy of config
                    below_block <- config[[i]][[2]]
                    new_config[[j]][[1]] <- i # Place block i on block j
                    new_config[[i]][[2]] <- j # Block i is now on block j
                    if (below_block != -1) { # Clear the block below if necessary
                        new_config[[below_block]][[1]] <- -1
                    }

                    action <- paste0("Move(", objects[i], ",", ifelse(below_block == -1, "table", objects[below_block]), ",", objects[j], ")")
                    child <- list(
                        config = new_config,
                        parent = state,
                        action = action,
                        cost = state$cost + 1,
                        depth = state$depth + 1 # Increment depth
                    )
                    children <- append(children, list(child))
                }
            }
        }
    }

    return(children)
}

trace_solution <- function(goal_state) {
    actions <- character(0)
    current <- goal_state

    # Trace actions back from the goal state
    while (!is.null(current$parent)) {
        actions <- c(actions, current$action) # Add action to the list
        current <- current$parent # Move to the parent state
    }

    return(rev(actions)) # Reverse to get actions in the correct order
}

simulate_move <- function(config, move, objects) {
    # Parse the move string (expected format: "Move(block,from,to)")
    # We will ignore the recorded "from" value and recompute it.
    action <- gsub("^Move\\(|\\)$", "", move)
    parts <- strsplit(action, ",")[[1]]
    block <- parts[1]
    # given_from <- parts[2]  # Ignored
    to <- parts[3]

    # Create a deep copy of config (each element is a list: [above, below])
    new_config <- lapply(config, function(x) list(x[[1]], x[[2]]))

    # Determine the index of the moving block
    i <- match(block, objects)

    # Ensure the moving block is clear
    if (new_config[[i]][[1]] != -1) {
        stop(paste("Illegal move:", move, "- block", block, "is not clear."))
    }

    # Remove block i from its current support (if any)
    current_support <- new_config[[i]][[2]]
    if (current_support != -1) {
        new_config[[i]][[2]] <- -1
        new_config[[current_support]][[1]] <- -1
    }

    # Now, apply the destination specified by the move:
    if (to == "table") {
        new_config[[i]][[2]] <- -1
    } else {
        j <- match(to, objects)
        # Check that the destination block is clear
        if (new_config[[j]][[1]] != -1) {
            stop(paste("Illegal move:", move, "- destination block", to, "is not clear."))
        }
        new_config[[i]][[2]] <- j
        new_config[[j]][[1]] <- i
    }

    return(new_config)
}


# A helper function that counts how many blocks are <U+201C>correctly placed.<U+201D>
# A block is considered correctly placed if its "below" pointer matches that in the goal.
count_correct <- function(config, goal_config) {
    correct <- 0
    for (i in seq_along(config)) {
        if (config[[i]][[2]] == goal_config[[i]][[2]]) {
            correct <- correct + 1
        }
    }
    return(correct)
}

# The simulation<U+2010>based optimal filter:
optimal_filter <- function(actions, begin_config, goal_config, objects) {
    current_config <- begin_config
    essential_moves <- c()

    # Compute how many blocks are in the correct position initially.
    current_correct <- count_correct(current_config, goal_config)

    for (move in actions) {
        new_config <- simulate_move(current_config, move, objects)
        new_correct <- count_correct(new_config, goal_config)

        # Only add the move if it improves the number of correctly placed blocks.
        if (new_correct > current_correct) {
            essential_moves <- c(essential_moves, move)
            current_config <- new_config
            current_correct <- new_correct
        }
    }

    return(essential_moves)
}


# Helper: Convert a configuration into a unique string representation.
serialize_config <- function(config) {
    # Each block’s status (its above and below pointers) is joined with a comma,
    # and then blocks are joined with a semicolon.
    s <- sapply(config, function(x) paste(x, collapse = ","))
    return(paste(s, collapse = ";"))
}

# The original incremental improvement filter.
optimal_filter <- function(actions, begin_config, goal_config, objects) {
    current_config <- begin_config
    essential_moves <- c()

    # Compute how many blocks are in the correct position initially.
    current_correct <- count_correct(current_config, goal_config)

    for (move in actions) {
        new_config <- simulate_move(current_config, move, objects)
        new_correct <- count_correct(new_config, goal_config)

        # Only add the move if it improves the number of correctly placed blocks.
        if (new_correct > current_correct) {
            essential_moves <- c(essential_moves, move)
            current_config <- new_config
            current_correct <- new_correct
        }
    }

    return(essential_moves)
}


# Simple filter for when the initial configuration is all on the table.
simple_optimal_filter <- function(goal_config, objects) {
    essential_moves <- c()

    # Identify the base blocks in the goal configuration (blocks on table)
    base_indices <- which(sapply(goal_config, function(x) x[[2]] == -1))

    # For each base, follow the chain upward
    for (base in base_indices) {
        current <- base
        repeat {
            # In our representation, if block j is placed on block current,
            # then goal_config[[j]][[2]] == current.
            next_block <- which(sapply(seq_along(goal_config), function(j) goal_config[[j]][[2]] == current))
            if (length(next_block) == 0) break # no block on top of current in the goal
            next_block <- next_block[1] # assume a single chain per stack
            move_str <- paste0("Move(", objects[next_block], ",table,", objects[current], ")")
            essential_moves <- c(essential_moves, move_str)
            current <- next_block
        }
    }

    return(essential_moves)
}


# Helper: Convert a configuration into a unique string representation.
serialize_config <- function(config) {
    # Each block’s status is joined with a comma, and then blocks are joined with a semicolon.
    s <- sapply(config, function(x) paste(x, collapse = ","))
    return(paste(s, collapse = ";"))
}


# DP-based filter: Given a list of DFS moves, extract a minimal subsequence (by removing cycles)
dp_filter <- function(actions, begin_config, objects) {
    # Step 1. Simulate the DFS solution to obtain the sequence of states.
    # states[i] will be the serialized configuration after i-1 moves.
    N <- length(actions) + 1
    states <- vector("list", N)
    current_config <- begin_config
    states[[1]] <- serialize_config(current_config)

    for (i in 1:length(actions)) {
        new_config <- tryCatch(
            simulate_move(current_config, actions[i], objects),
            error = function(e) {
                message("Skipping illegal move during DP simulation: ", actions[i], " (", e$message, ")")
                return(NA)
            }
        )
        if (is.null(new_config)) {
            states[[i + 1]] <- NA
        } else {
            current_config <- new_config
            states[[i + 1]] <- serialize_config(new_config)
        }
    }

    # Step 2. Build the graph edges.
    # We'll define nodes 1...N corresponding to states[1]...states[N].
    # There is always an edge from i to i+1 with cost 1 (using move i).
    # Also, for any i < j, if states[[i]] equals states[[j]] (and not NA), add an edge from i to j with cost 0.
    # We then compute the minimal cost (number of moves used) from node 1 to node N.

    dp_cost <- rep(Inf, N) # dp_cost[i] = minimal cost to reach state i
    prev_node <- rep(NA, N) # To reconstruct the path
    dp_cost[1] <- 0

    for (i in 1:(N - 1)) {
        # Always consider the edge from i to i+1 (cost 1)
        if (dp_cost[i] + 1 < dp_cost[i + 1]) {
            dp_cost[i + 1] <- dp_cost[i] + 1
            prev_node[i + 1] <- i
        }
        # Look for any j > i+1 such that states[[i]] == states[[j]]
        if (!is.na(states[[i]])) {
            if ((i + 2) <= N) { # Only loop if there is at least one j
                for (j in (i + 2):N) {
                    if (!is.na(states[[j]]) && states[[i]] == states[[j]]) {
                        # Taking the edge from i directly to j costs 0 additional moves.
                        if (dp_cost[i] < dp_cost[j]) {
                            dp_cost[j] <- dp_cost[i]
                            prev_node[j] <- i
                        }
                    }
                }
            }
        }
    }

    # If no path was found (should not happen), return the original actions.
    if (is.infinite(dp_cost[N])) {
        message("DP filter: no valid path found; returning original actions.")
        return(actions)
    }

    # Step 3. Reconstruct the path from node N back to node 1.
    path_nodes <- c()
    cur <- N
    while (!is.na(cur)) {
        path_nodes <- c(cur, path_nodes)
        cur <- prev_node[cur]
    }

    # Step 4. Extract the moves corresponding to the edges that have cost 1.
    # (An edge from i to i+1 indicates that move i was used; an edge from i to j with j>i+1 means a cycle was skipped.)
    optimized_moves <- c()
    for (k in 1:(length(path_nodes) - 1)) {
        from <- path_nodes[k]
        to <- path_nodes[k + 1]
        if (to == from + 1) {
            # This edge represents that we kept move number 'from'
            optimized_moves <- c(optimized_moves, actions[from])
        }
        # Otherwise, the edge had cost 0, so we skipped moves in between.
    }

    return(optimized_moves)
}


# Global counters for metrics
nodes_expanded <<- 0
max_search_depth_global <<- 0

# Depth-First Search Implementation
dfs_search <- function(initial_state, goal_config, objects, max_depth, max_cost) {
    stack <- list(initial_state)
    explored <- list()

    while (length(stack) > 0) {
        # Pop the last state from the stack
        state <- stack[[length(stack)]]
        stack <- stack[-length(stack)]

        # Add the current state to explored
        explored <- append(explored, list(state$config))

        # Update metrics
        nodes_expanded <<- nodes_expanded + 1
        if (state$depth > max_search_depth_global) {
            max_search_depth_global <<- state$depth
        }

        # Check if the goal state is reached
        if (identical(state$config, goal_config)) {
            return(state) # Return the solution without printing
        }

        # Check depth and cost constraints
        if (state$cost > max_cost || state$depth > max_depth) {
            next # Skip this state if it exceeds the constraints
        }

        # Expand the current state and add children to the stack
        children <- expand_state(state, objects, explored)
        stack <- append(stack, children)
    }

    stop("DFS failed to find a solution within the depth and cost constraints.")
}



# Breadth-First Search Implementation
bfs_search <- function(initial_state, goal_config, objects) {
    frontier <- list(initial_state)
    explored <- list()

    while (length(frontier) > 0) {
        state <- frontier[[1]]
        frontier <- frontier[-1]

        # Add the current state to explored
        explored <- append(explored, list(state$config))

        # Check if the goal state is reached
        # print_config(state$config, objects, "compare state")
        # print_config(goal_config, objects, "goal")

        nodes_expanded <<- nodes_expanded + 1
        if (state$depth > max_search_depth_global) {
            max_search_depth_global <<- state$depth
        }

        if (identical(state$config, goal_config)) {
            cat("Goal state reached with BFS\n")
            return(state)
        }

        # Expand the current state and filter children
        children <- expand_state(state, objects, explored)

        for (child in children) {
            # Check for duplicate states in the frontier
            is_in_frontier <- any(sapply(frontier, function(s) identical(s$config, child$config)))
            if (!is_in_frontier) {
                frontier <- append(frontier, list(child))
            }
        }
    }

    stop("BFS failed to find a solution.")
}


# Main Program

args <- commandArgs(trailingOnly = TRUE) # Get command-line arguments
if (length(args) != 3) stop("Usage: Rscript blocks.R depth|breadth input_file output_file")

# Parse the first argument to determine search type
search_type <- args[1] # "depth" or "breadth"
if (!search_type %in% c("depth", "breadth")) {
    stop("Usage: Rscript script.R depth|breadth input_file output_file")
}

# Get input and output file paths
input_file <- args[2] # Second argument (input file)
output_file <- args[3] # Third argument (output file)

# Parse input
parsed <- parse_file(input_file)

# Sort objects alphabetically
objects <- sort(parsed$objects)

# Parse configurations
begin_config <- parse_config(objects, parsed$filtered_init)
goal_config <- parse_config(objects, parsed$filtered_goal)

# Print initial and goal configurations for debugging
print_config(begin_config, objects, "Initial Configuration")
print_config(goal_config, objects, "Goal Configuration")

initial_state <- list(
    config = begin_config,
    parent = NULL,
    action = NULL,
    cost = 0,
    depth = 0 # Initial depth is 0
)

max_depth <- 10 # Maximum depth of the search
max_cost <- 10 # Maximum cost of the search

# Perform the chosen search
start_time <- Sys.time()
if (search_type == "depth") {
    solution <- dfs_search(initial_state, goal_config, objects, max_depth, max_cost)
} else if (search_type == "breadth") {
    solution <- bfs_search(initial_state, goal_config, objects)
}
running_time <- as.numeric(Sys.time() - start_time, units = "secs")

# Trace actions to reach the goal
actions <- trace_solution(solution)
write_lines(actions, "all_actions.txt")

# Determine if all blocks are on the table in the initial configuration
all_on_table <- all(sapply(begin_config, function(x) x[[2]] == -1))

if (all_on_table) {
    optimized_actions <- simple_optimal_filter(goal_config, objects)
} else {
    optimized_actions <- dp_filter(actions, begin_config, objects)
}
running_time <- as.numeric(Sys.time() - start_time, units = "secs")
cat("running_time: ", running_time, "\n")

# Write optimized actions to the output file
# Add spaces after commas
optimized_actions <- gsub(",", ", ", optimized_actions)
write_lines(optimized_actions, output_file)
cat("Optimized actions written to", output_file, "\n")
