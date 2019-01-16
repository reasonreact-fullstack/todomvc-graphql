let styles: ToDoHeaderStyles.definition = [%raw {| require("./ToDoHeader.scss") |}]
let component = ReasonReact.statelessComponent("ToDoHeader")

let make = (~submit, ~completeAll, _children) => {
    ...component,

    render: _self => {
        <div className=styles##wrap>
            <ToDoCheckAllButton completeAll />
            <ToDoInput 
                newTodo=true 
                placeholder="What needs to be done?" 
                submit
            />
        </div>
    }
}
