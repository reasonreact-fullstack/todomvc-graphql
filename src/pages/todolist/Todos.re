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

let count = ref(0);
let counter = () => {
    count := count^ + 1;
    count^
}

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
            todos: state.todos -> List.append([{
                ...newItem,
                id: counter(),
            }]) 
        })
        | CompleteAll => ReasonReact.Update({ 
            ...state, 
            todos: state.todos 
                |> todos => {
                    let countIncompleted = todos 
                        |> List.filter((todo:todoItem) => {
                            !todo.completed
                        })
                        |> List.length
                    countIncompleted == 0
                }
                |> allCompleted => {
                    state.todos |> List.map((todo:todoItem) => {
                        ...todo, 
                        completed: !allCompleted,
                    })
                }
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
        Js.log(self.state.todos);

        <div className=styles##wrap>
            <ToDoHeader 
                submit={ todo => self.send(AddNew(todo)); } 
                completeAll={ () => self.send(CompleteAll) }
            />
            <ToDoItemList 
                todos=self.state.todos 
                toggleTodo={ todo => self.send(Toggle(todo)) }
                submit={ todo => self.send(Edit(todo))}
            />
            <ToDoFooter />
        </div>
    }
}
