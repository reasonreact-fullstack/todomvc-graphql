let styles: ToDoHeaderStyles.definition = [%raw {| require("./ToDoHeader.scss") |}]
let component = ReasonReact.statelessComponent("ToDoHeader")

let make = (_children) => {
    ...component,

    render: _self => {
        <div className=styles##wrap>
            <ToDoCheckAllButton />
            <ToDoInput newTodo=true placeholder="What needs to be done?" />
        </div>
    }
}
