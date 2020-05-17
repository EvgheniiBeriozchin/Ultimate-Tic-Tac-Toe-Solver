#include <TranspositionTable.h>

TranspositionTable::TranspositionTable()
{
    this->hit_counter = 0;
}

TranspositionTable::TranspositionTable(mongocxx::collection collection)
{
    this->hit_counter = 0;

    auto cursor = collection.find({});
    for (auto&& doc : cursor) {
        auto item = bsoncxx::to_json(doc);
        this->transposition_table[doc["key"].get_utf8().value.to_string()] = doc["value"].get_int32().value;
    }

    cout << "Transposition table created with " << this->transposition_table.size() << " items." << endl;
}

void TranspositionTable::set(Board board, int value)
{
    string string_board = board.to_string();
    int board_moves = board.get_number_of_moves();
    if (this->biggest_boards.size() < STACK_SIZE)
    {
        this->biggest_boards.push(make_pair(string_board, board_moves));
    }
    else
    {
        if (this->biggest_boards.top().second <= board_moves)
        {
            this->biggest_boards.push(make_pair(string_board, board_moves));
            string_board = this->biggest_boards.top().first;
            this->biggest_boards.pop();
        }

        if (this->latest_boards.size() == STACK_SIZE)
            this->latest_boards.pop();
        this->latest_boards.push(string_board);
    }

    this->transposition_table[string_board] = value; 
}


int TranspositionTable::get(Board board)
{
    string key = board.to_string();
    if (this->transposition_table.find(key) == this->transposition_table.end())
        return 0;
    this->hit_counter++;
    
    return this->transposition_table.at(key); 
}

int TranspositionTable::get_hit_counter()
{
    return this->hit_counter;
}

int TranspositionTable::dump_to_db(mongocxx::collection collection)
{
    int items_added = 0;

    for (auto& item: this->transposition_table) {

        bsoncxx::builder::stream::document document{};
        if (!collection.count_documents(document << "key" << item.first << bsoncxx::builder::stream::finalize))
        {
            bsoncxx::builder::stream::document document{};
            document << "key" << item.first
            << "value" << item.second;
            collection.insert_one(document.view());
            items_added++;
        }
    }

    return items_added;
}
