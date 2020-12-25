#include "dfa.h"

/**
 * Initialize a new automaton with a set number of states
 *
 * Note: don't forget to free
 */
struct dfa *new_dfa(unsigned int states_count) {
    struct dfa *d;

    d = (struct dfa *) malloc(sizeof(struct dfa));
    d->states_count = states_count;

    d->final_states = (bool *) malloc(sizeof(bool) * states_count);
    set_all(d->final_states, states_count, false);

    return d;
}

/**
 * Return an ftransition
 *
 * Note: don't forget to free
 */
struct ftransition new_ftransition(unsigned int start_state, unsigned char c,
                                   unsigned int dest_state) {

    return (struct ftransition) { start_state, c, dest_state };
}

/**
 * Checks if word can be accepted by the automaton d
 */
bool accept(struct dfa *d, unsigned char *word) {
    unsigned int current_state;
    bool is_accepted;
    size_t i;
    struct ftransition transition;

    current_state = 0;
    i = 0;
    is_accepted = true;

    while (is_accepted && i != strlen(word)) {
        transition = find_transition_with_start_state_and_symbol(d, current_state, word[i]);

        if (eql_ftransition(null_transition(), transition)) {
            is_accepted = false;
        } else {
            current_state = transition.dest_state;
        }

        i++;
    }

    // Check if current_state is a final state
    return (is_accepted && d->final_states[current_state]);
}

struct ftransition null_transition() {
    return (struct ftransition) { 0 , 0, 0 };
}

/**
 * Checks if 2 transitions are the same
 * TODO use memcmp, overkill but awesome af
 */
bool eql_ftransition(struct ftransition f1, struct ftransition f2) {
    return (f1.start_state == f2.start_state
            && f1.symbol == f2.symbol && f1.dest_state == f2.dest_state);
}

struct ftransition find_transition_with_start_state_and_symbol(struct dfa *d,
                                                               unsigned int start_state,
                                                               unsigned char symbol) {
    size_t i;
    bool found;
    struct ftransition trans;

    i = 0;
    found = false;

    while (!found && i != d->func->len) {
        trans = d->func->transitions[i];

        if (trans.start_state == start_state && trans.symbol == symbol) {
            found = true;
        }

        i++;
    }

    if (found)
        return trans;
    else
        return null_transition();
}


struct function_array *new_function_array(size_t len) {
    struct function_array *fa;

    fa = (struct function_array *) calloc(sizeof(struct function_array), 1);

    fa->transitions = (struct ftransition*) calloc(sizeof(struct ftransition), len);
    fa->len = len;

    return fa;
}

void free_dfa(struct dfa *d) {
    free(d->func->transitions);
    free(d->func);
    free(d->final_states);
    free(d->alphabet);
    free(d);
}

void free_function_array(struct function_array *fa) {
    free(fa->transitions);
    free(fa);
}

/**
 * Minimize a deterministic finite automaton
 *
 * 1) Assign a number to each state (1 if final, else 0)
 * 2) Write a table of the transitions using the number in step 1
 * 3) Check which states have the same transitions for all symbols, and assign
 * the same number for those states
 * 4) Repeat till we got a steady result (states)
 * 5) We create the transitions using the table before
 * 6) We check which among the new states are final states
 *
 * TODO refactor this, way too big
 */
struct dfa *dfa_minimization(struct dfa *d) {
    struct uintvv *table;
    struct ftransition trans;
    struct uintv *states, *states_before;
    bool *done;
    unsigned int new_states_count, states_count;
    struct dfa *dfa_minimized;
    size_t z, y;


    states = new_uintv(d->states_count);
    states_before = new_uintv(d->states_count);
    states_count = d->states_count;
    table = new_uintvv(states_count, strlen(d->alphabet));

    // initialization
    for (size_t i = 0; i != states_count; i++) {
        if (d->final_states[i]) {
            states->v[i] = 1;
        } else {
            states->v[i] = 0;
        }
    }

    z = 0;
    // We loop till we reach the same conclusion twice
    while (z < 2 || !eql_uintv(states_before, states)) {
        copy_uintv(states_before, states);
        for (size_t start_state = 0; start_state != states_count; start_state++) {
            for (size_t s = 0; s != strlen(d->alphabet); s++) {
                trans = find_transition_with_start_state_and_symbol(d, start_state, d->alphabet[s]);
                table->vv[start_state]->v[s] = states->v[trans.dest_state];
            }
        }
        deduce_states(table, states);

        z++;
    }

    // initial state is 0, so we add 1
    new_states_count = states->v[states_count - 1] + 1;

    dfa_minimized = new_dfa(new_states_count);
    dfa_minimized->func = new_function_array(new_states_count * strlen(d->alphabet));
    done = (bool *) malloc(sizeof(bool) * new_states_count);

    // set all values to false
    set_all(done, new_states_count, false);

    // We create the transitions
    // i : symbol
    // j : start state
    y = 0;
    for (size_t j = 0; j != table->len; j++) {
        int z;

        // Since some columns may be redundant, we check in a boolean
        // array if we already checked them
        z = (int) states->v[j];
        if (done[z]) {
            continue;
        }
        for (size_t i = 0; i != strlen(d->alphabet); i++) {
            trans = new_ftransition(states->v[j], d->alphabet[i], table->vv[j]->v[i]);

            dfa_minimized->func->transitions[y] = trans;
            y++;
        }
        done[z] = true;
    }

    // set all values to false
    set_all(done, new_states_count, false);

    // deduce final states
    for (size_t i = 0; i != states_count; i++) {
        int j = (int) states->v[i];

        if (!done[j] && d->final_states[i]) {
            dfa_minimized->final_states[j] = true;
            done[j] = true;
        }
    }



    dfa_minimized->alphabet = (unsigned char *) calloc(1, strlen(d->alphabet) + 1);
    strcpy(dfa_minimized->alphabet, d->alphabet);

    free_uintv(states);
    free_uintv(states_before);
    free(done);
    free_uintvv(table);

    return dfa_minimized;
}

void append_transition(struct function_array *fa, struct ftransition t) {
    fa->transitions = realloc(fa->transitions, sizeof(struct ftransition) * (fa->len + 1));
    fa->transitions[fa->len] = t;
    fa->len++;
}

/**
 * Assign integers for arrays that are equal. The result is stocked in
 * variable states
 *
 * Example:
 * table = [[1, 1, 2], [0, 0, 0], [1, 1, 2]]
 * The result will be:
 * states = [0, 1, 0]
 */
void deduce_states(struct uintvv *table, struct uintv *states) {
    bool *done;
    unsigned int current_state;

    current_state = 0;
    done = (bool *) malloc(sizeof(bool) * states->len);
    set_all(done, states->len, false);

    for (size_t i = 0; i != states->len; i++) {
        if (done[i]) {
            continue;
        } else {
            states->v[i] = current_state;
            done[i] = true;
        }

        // for each row we check if the array at index j is equal to the array
        // at index i
        for (size_t j = i + 1; j != states->len; j++) {
            if (eql_uintv(table->vv[i], table->vv[j])) {
                states->v[j] = current_state;
                done[j] = true;
            }
        }
        current_state++;
    }

    free(done);
}


void print_dfa(struct dfa *d) {
    printf("states_count : %d\n", d->states_count);

    printf("final_states : ");

    for (size_t i = 0; i != d->states_count; i++) {
        if (d->final_states[i] == true) {
            printf("%d ", i);
        }
    }

    printf("\ntransitions : \n");
    for (size_t i = 0; i != d->func->len; i++) {
        printf("\t%d, ", d->func->transitions[i].start_state);
        printf("%c, ", d->func->transitions[i].symbol);
        printf("%d\n", d->func->transitions[i].dest_state);
    }
}

void print_transitions(struct function_array *fa) {
    printf("\ntransitions : \n");
    for (size_t i = 0; i != fa->len; i++) {
        printf("\t%d, ", fa->transitions[i].start_state);
        printf("%c, ", fa->transitions[i].symbol);
        printf("%d\n", fa->transitions[i].dest_state);
    }
}


#if 1==2

/**
 * Return the destinations for a given state and a given symbol
 * Note: don't forget to free_uintv
 */
struct uintv *get_destinations_states_for(af_s *afn, unsigned int start_state, unsigned char symbol) {
    struct uintv *destinations;

    destinations = new_uintv(0);

    for (size_t i = 0; i != afn->tr[start_state]->size; i++) {
        if (afn->tr[start_state]->symbols[i] == symbol) {
            append_uintv(afn->tr[start_state]->destinations[i]);
        }
    }

    return destinations;
}

/**
 * Convertit un automate fini non déterministe en un automate fini déterministe
 *
 */
struct dfa *nfa_to_dfa(af_s *afn) {
    struct dfa *d;
    unsigned char *alphabet;
    struct function_array *transitions;
    struct uintv *destinations, *all_destinations;
    struct uintvv *states_array;
    bool *new_final_states;

    /* TODO remove this line
     * there's no field for the alphabet in the struct af_s :/
     * so there's no choice but to create it here, and add to the dfa later
     */
    alphabet = get_ascii_table();

    for (size_t t = 0; t != states_array->len; t++) {
        for (size_t s = 0; s != strlen(alphabet); s++) {
            for (size_t i = 0; i != states_array->vv[t]->len; i++) {
                /* TODO modify struct af_s
                 * Would have been better if the transitions were a field
                 * (start_state, symbol, array_of_destinations)
                 * Better complexity for the method below
                 * get_destinations_states_for()
                 */
                destinations = get_destinations_states_for(states_array->vv[t]->v[i], s);
                concat_uintv(all_destinations, destinations);
                free_uintv(destinations);
            }

            index = get_index_uintvv(states_array, all_destinations);

            // meaning states_array contains all_destinations
            if (index < states_array->len) {
                append_transition(transitions, new_ftransition(t, s, index));
            } else {
                append_uintvv(states_array, all_destinations);
                append_transition(transitions, new_ftransition(t, s, states_array->len - 1));
            }
        }
    }

    d = new_dfa(states_array->len);

    // TODO get final states
    for (size_t z = 0; z != states_array->len; z++) {
        size_t y = 0;
        while (y != states_array->vv[z]->len && !d->final_states) {
            int index = (int) states_array->vv[z]->v[y];

            if (afn->final_states[index]) {
                d->final_states[z] = true;
            }
            y++;
        }
    }

    dfa_minimized->alphabet = (unsigned char *) calloc(1, strlen(d->alphabet) + 1);
    strcpy(dfa_minimized->alphabet, d->alphabet);

    free_uintv(all_destinations);
    free_uintvv(states_array);

    return d;
}
#endif


// TODO put in utils, totally unrelated here
unsigned char *get_ascii_table() {
    unsigned char *ascii_table;

    ascii_table = (unsigned char *) calloc(257, sizeof(unsigned char));
    for (size_t i = 0; i != 256; i++) {
        ascii_table[i] = i;
    }

    return ascii_table;
}

/**
 * Set all values of an array of boolean
 *
 * TODO do a struct boolv for boolean vectors
 */
void set_all(bool *bool_array, size_t len, bool value) {
    for (size_t i = 0; i != len; i++) {
        bool_array[i] = value;
    }
}