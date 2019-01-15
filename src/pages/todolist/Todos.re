let styles: TodosStyles.definition = [%raw {| require("./Todos.scss") |}]

let component = ReasonReact.statelessComponent("Todos")

let make = (_children) => {
    ...component,

    render: _self => {
        <div className=styles##wrap>
            <ToDoHeader />
        </div>
    }
}
