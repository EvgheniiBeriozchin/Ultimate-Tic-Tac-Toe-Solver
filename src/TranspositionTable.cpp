#include <TranspositionTable.h>

TranspositionTable::TranspositionTable(int tt_type, int size)
{
    this->hit_counter = 0;
    this->query_counter = 0;
    this->type = tt_type;
    if (this->type > 2)
        this->size = size/2;
    else
        this->size = size;
    
    
}
/*
TranspositionTable::TranspositionTable(mongocxx::collection collection, int tt_type, int size)
{
    
    this->hit_counter = 0;
    this->query_counter = 0;
    this->type = tt_type;
    this->size = size;
    
    int j = 0;
    auto cursor = collection.find({});
    for (auto&& doc : cursor) {
        auto item = bsoncxx::to_json(doc);
        string key = doc["key"].get_utf8().value.to_string();
        this->latest_boards.push(key);
        this->transposition_table[key] = doc["value"].get_int32().value;
        if (++j >= STACK_SIZE)
            break;
    }

    cout << "Transposition table created with " << this->transposition_table.size() << " items." << endl;
    
}
*/
void TranspositionTable::set(Board board, int value, int size)
{
    if (this->type == 0)
        return;

    if (this->type > 1 && this->biggest_boards.size() >= this->size && this->biggest_boards.top().second <= size)
    {
        Board board_to_erase = this->biggest_boards.top().first;
        this->erase_board(board_to_erase);
        this->biggest_boards.pop();
        this->biggest_boards.push(make_pair(board, size));
    }
    else if (this->type > 1 && this->biggest_boards.size() < this->size)
    {
        this->biggest_boards.push(make_pair(board, size));
    }
    else if (this->type % 2 == 1)
    {
        this->insert_latest_board(board, value);
    }

    this->transposition_table[board.get_board(0)][board.get_board(1)][board.get_board(2)] = value;
}

void TranspositionTable::insert_latest_board(Board board, int value)
{
    if (this->latest_boards.size() >= this->size)
    {
        Board board_to_erase = this->latest_boards.top();
        this->latest_boards.pop();
        this->erase_board(board_to_erase);
    }

    this->latest_boards.push(board);
}

void TranspositionTable::erase_board(Board board_to_erase)
{
    this->transposition_table[board_to_erase.get_board(0)][board_to_erase.get_board(1)].erase(board_to_erase.get_board(2));
    if (this->transposition_table[board_to_erase.get_board(0)][board_to_erase.get_board(1)].size() == 0)
        this->transposition_table[board_to_erase.get_board(0)].erase(board_to_erase.get_board(1));
    if (this->transposition_table[board_to_erase.get_board(0)].size() == 0)
        this->transposition_table.erase(board_to_erase.get_board(0));
}

int TranspositionTable::get(Board board)
{
    if (this->type == 0)
        return 0;

    this->query_counter++;
    if (this->transposition_table.find(board.get_board(0)) == this->transposition_table.end()
        || this->transposition_table[board.get_board(0)].find(board.get_board(1)) == this->transposition_table[board.get_board(0)].end()
        || this->transposition_table[board.get_board(0)][board.get_board(1)].find(board.get_board(2)) == this->transposition_table[board.get_board(0)][board.get_board(1)].end())
        return 0;
    
    this->hit_counter++;
    return this->transposition_table[board.get_board(0)][board.get_board(1)].at(board.get_board(2)); 
}

double TranspositionTable::get_hit_ratio()
{
    if (this->query_counter > 0) 
        return this->hit_counter/(double)this->query_counter;
    else return -1.0;
}

int TranspositionTable::get_size()
{
    if (this->type > 2)
        return this->size * 2;
    else
        return this->size;
}
/*
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
*/