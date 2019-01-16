let styles: TodosStyles.definition = [%raw {| require("./Todos.scss") |}]

type todoItem = ToDoTypes.todo;

type filter = All | Active | Completed

type state = {
    todos: list(todoItem),
    filter: filter,
};

type action = 
    | AddNew(todoItem)
    | CompleteAll 
    | Toggle(todoItem)
    | Edit(todoItem)
    | Remove(int)
    | Filter(filter)
    | RemoveCompleted;

let component = ReasonReact.reducerComponent("Todos");

let make = (_children) => {
    ...component,
    initialState: () => {
        todos: [
            { id: 0, content: "Learn how this works", completed: false, },
        ],
        filter: All,
    },

    reducer: (action: action, state: state) => {
        switch(action) {
        | AddNew(newItem) => ReasonReact.Update({ 
            ...state, 
            todos: state.todos |> List.append([newItem]) 
        })
        | CompleteAll => ReasonReact.Update({ 
            ...state, 
            todos: state.todos |> List.map((todo:todoItem) => {
                ...todo, 
                completed: true
            })
        })
        | Toggle(toggledItem) => ReasonReact.Update({
            ...state,
            todos: state.todos |> List.map((todo:todoItem) => {
                switch(todo.id == toggledItem.id) {
                | true => { ...todo, completed: !todo.completed }
                | false => todo
                }
            })
        })
        | Edit(editedItem) => ReasonReact.Update({
            ...state,
            todos: state.todos |> List.map((todo:todoItem) => {
                switch(todo.id == editedItem.id) {
                | true => { ...todo, content: editedItem.content }
                | false => todo
                }
            })
        })
        | Remove(removedID) => ReasonReact.Update({
            ...state,
            todos: state.todos |> List.filter((todo:todoItem) => {
                todo.id != removedID;
            })
        })
        | Filter(filter) => ReasonReact.Update({
            ...state,
            filter: filter,
        })
        | RemoveCompleted => ReasonReact.Update({
            ...state,
            todos: state.todos |> List.filter((todo:todoItem) => !todo.completed)
        })
        }
    },

    render: self => {
        <div className=styles##wrap>
            <ToDoHeader />
            <ToDoItemList todos=self.state.todos />
            <ToDoFooter />
        </div>
    }
}
