let styles: ToDoFilterStyles.definition = [%raw {| require("./ToDoFooter.scss") |}]
let component = ReasonReact.statelessComponent("ToDoFilter")

let make = (_children) => {
    ...component,

    render: _self => {
        <div className=styles##wrap>
            <span className=styles##count>{ ReasonReact.string("1 item left") }</span>
            <ul className=styles##filters>
                <li><button className=styles##filter>{ ReasonReact.string("All") }</button></li>
                <li><button className=styles##filter>{ ReasonReact.string("Active") }</button></li>
                <li><button className=styles##filter>{ ReasonReact.string("Completed") }</button></li>
            </ul>
            <button className=styles##removeCompleted>{ ReasonReact.string("Clear Completed") }</button>
        </div>
    }
}
