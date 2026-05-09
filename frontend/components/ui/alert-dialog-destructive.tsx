import { Trash2Icon } from "lucide-react"

import {
    AlertDialog,
    AlertDialogAction,
    AlertDialogCancel,
    AlertDialogContent,
    AlertDialogDescription,
    AlertDialogFooter,
    AlertDialogHeader,
    AlertDialogMedia,
    AlertDialogTitle,
    AlertDialogTrigger,
} from "@/components/ui/alert-dialog"
import { Button } from "@/components/ui/button"

type AlertDialogDestructiveProps = {
    buttonTitle: string;
    dialogTitle: string;
    dialogDescription: string;
    dialogCancel: string;
    dialogAction: string;
    onConfirm?: () => void | Promise<void>;
};

export function AlertDialogDestructive(
    {
        buttonTitle,
        dialogTitle,
        dialogDescription,
        dialogCancel,
        dialogAction,
        onConfirm
    }: AlertDialogDestructiveProps
) {
    return (
        <AlertDialog>
            <AlertDialogTrigger asChild>
                <Button variant="destructive">{buttonTitle}</Button>
            </AlertDialogTrigger>
            <AlertDialogContent size="sm">
                <AlertDialogHeader>
                    <AlertDialogMedia className="bg-destructive/10 text-destructive dark:bg-destructive/20 dark:text-destructive">
                        <Trash2Icon />
                    </AlertDialogMedia>
                    <AlertDialogTitle>{dialogTitle}</AlertDialogTitle>
                    <AlertDialogDescription>
                        {dialogDescription}
                    </AlertDialogDescription>
                </AlertDialogHeader>
                <AlertDialogFooter>
                    <AlertDialogCancel variant="outline">{dialogCancel}</AlertDialogCancel>
                    <AlertDialogAction variant="destructive" onClick={onConfirm}>{dialogAction}</AlertDialogAction>
                </AlertDialogFooter>
            </AlertDialogContent>
        </AlertDialog>
    )
}