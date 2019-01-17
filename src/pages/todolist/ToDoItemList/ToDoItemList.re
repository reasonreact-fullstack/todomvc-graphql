let styles: ToDoItemListStyles.definition = [%raw {| require("./ToDoItemList.scss") |}]

type todoItem = ToDoTypes.todo;

let component = ReasonReact.statelessComponent("ToDoItemList")

let make = (
    ~todos: list(ToDoTypes.todo), 
    ~toggleTodo: todoItem => unit,
    ~submit: todoItem => unit,
    _children
) => {
    ...component,

    render: _self => {
        <div className=styles##wrap>
            <ul className=styles##list>
            {ReasonReact.array(Array.map((todo:ToDoTypes.todo) => {
                <ToDoItem key=string_of_int(todo.id) todo toggleTodo submit />
            }, Array.of_list(todos)))}
            </ul>
        </div>
    }
}
