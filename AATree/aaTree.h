template <typename T>
class aaTree
{
    public:
        aaTree();
        ~aaTree();

        void insert(T & data);
        void inOrder();
        bool contains(T & data);
        void remove(T & data);
        void clear();

    private:
        struct Node 
        {
            T data; 
            int level;
            Node * left;
            Node * right;

            Node(int _data) 
            {
                this -> data = _data;
                level = 1;
                left = nullptr;
                right = nullptr;
            }

            Node(T _data, int level, Node * left, Node * right)
            {
                this -> data = _data;
                this -> level = level;
                this -> left = left;
                this -> right = right;
            }

            bool operator==(const Node& other) const {
                return data == other.data && level == other.level;
            }
        };

        Node * root;

        Node * insert(Node * node, T & data);
        Node * skew(Node * node);
	    Node * split(Node * node);
	    Node * remove(Node * node, T & data);
	    void inOrder(Node * node);
	    void clear(Node * node);

};

// конструктор без параметров
template <typename T>
aaTree<T>::aaTree()
{
    this -> root = nullptr;
}

// деструктор
template <typename T>
aaTree<T>::~aaTree()
{
    clear();
}

// пользовательский метод, который вызывает внутренний
template <typename T>
void aaTree<T>::insert(T & data) 
{
    root = insert(root, data);
}

// node - корень дерева (поддерева), куда вставляется узел со значением data
template <typename T>
typename aaTree<T>::Node * aaTree<T>::insert(Node * node, T & data) 
{
    // если узел отсутствует, создаем его
    if (node == nullptr) 
    {
        return new Node(data);
    }
    // идем влево, если data меньше значения корня текущего поддерева
    else if (data < node->data)
    {
        node->left = insert(node->left, data);
    }
    // идем вправо, если data больше значения корня текущего поддерева
    else if (data > node->value)
    {
        node->right = insert(node->right, data);
    }
    else {
        return node;
    }

    // балансировка дерева
    node = skew(node);
    node = split(node);

    return node;
}

/* 
    метод для устранения левого горизонтального ребра; поворачиваем вправо, чтобы заменить поддерево, 
    содержащее левую горизонтальную связь, на поддерево, содержащее разрешенную правую горизонтальную связь
*/ 
template <typename T>
typename aaTree<T>::Node * aaTree<T>::skew(Node * node) 
{
    // если узел пуст, возвращаем null
    if (node == nullptr) {
        return nullptr;
    }
    // проверка наличия горизонтального ребра
    else if (node -> left != nullptr && node -> left -> level == node -> level) {
        return Node(
            node -> left,               // корнем становится левый для node узел
            node -> left -> level,      // уровень сохраняется
            node -> left -> left,       // левый ребенок остается прежним
            Node(
                node,                   // старый корень становится правым ребенком
                node -> level,          // уровень сохраняется
                node -> left -> right,  // левым ребенок становится правле поддерево
                node -> right           // правый ребенок остается прежним
            )
        );
    }
    // оставляем все как есть, если левых горизонтальных ребер нет
    else 
    {
        return node;
    }
}

/*
    метод для устранения двух последовательных правых горизонтальных ребер; поворачиваем влево и увеличиваем 
    уровень, чтобы заменить поддерево, содержащее две или более последовательных правых горизонтальных 
    связи, на вершину, содержащую два поддерева с меньшим уровнем
*/
template <typename T>
typename aaTree<T>::Node * aaTree<T>::split(Node * node) 
{
    // если узел пуст, возвращаем null
    if (node == nullptr) {
        return nullptr;
    }
    // проверяем, что правого потомка или его правого потомка не существует
    // иначе невозможно выполнить операцию из-за нехватки узлов
    else if (node -> right == nullptr || node -> right -> right == nullptr)
    {
        return node;
    }
    // проверяем совпадение текущего уровня с уровнем правого-правого потомка
    else if (node -> level == node -> right -> right -> level)
    {
        return Node(
            node -> right,                  // корнем становится правый для node узел
            node -> right -> level + 1,     // уровень поднимается на один
            Node (
                node,                       // левым потомком становится текущий узел
                node -> level,              // уровень остается прежним
                node -> left,               // левый потомок остается прежним
                node -> right -> left       // левым потомком становытся левый потомок правого потомка
            ),
            node -> right -> right,         // правым потомком становится правый потомок правого потомка
        );
    } 
    else {
        return node;
    }
}

// пользовательский метод, который вызывает внутренний
template <typename T>
void aaTree<T>::inOrder()
{
    inOrder(root);
}

// метод для обхода в дереве в порядке левое поддерево - корень - правое поддерево
template <typename T> 
void aaTree<T>::inOrder(Node * node)
{
    // базовый случай рекурсии - если дошли дальше листа
    if (node == nullptr) return;
    // идем в левое поддерево, пока не дойдем до базового случая
    inOrder(node -> left);
    // выводим элемент
    std::cout << node -> data << " -> ";
    // идем вправо
    inOrder(node -> right);
}

// метод для проверки наличия элемента в дереве
template <typename T>
bool aaTree<T>::contains(T & data)
{
    Node * currentNode = root;

    //пока не достигнем конца дерева
    while (currentNode != nullptr)
    {
        // найдено, если данные равны
       if (currentNode -> data == data) {
            return true;
       }
       // если data меньше текущего элемента, идем влево
       else if (currentNode -> data > data) 
       {
            currentNode = currentNode -> left;
       }
       // если data больше текущего элемента, идем вправо
       else 
       {
            currentNode = currentNode -> right;
       }
    }

    return false;
}